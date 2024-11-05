#include <cstddef>
#include <cassert>
#include <vector>
#include <memory_resource>
#include <memory>

class Arena : public std::pmr::memory_resource {
public:
    explicit Arena(size_t blockSize = 1024 * 1024) // Default 1MB
        : blockSize(blockSize), currentBlock(nullptr), currentPos(0) {
        allocateBlock();
    }

    ~Arena() override {
        for (auto block : blocks) {
            delete[] block;
        }
    }

    // Reset the arena to reuse memory
    void reset() {
        currentPos = 0;
        // Optionally, keep the first block and free the rest
        while (blocks.size() > 1) {
            delete[] blocks.back();
            blocks.pop_back();
        }
        currentBlock = blocks.front();
    }

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        assert(bytes > 0 && "Allocation size must be greater than 0");

        char* blockStart = currentBlock;
        char* currentPtr = blockStart + currentPos;

        std::size_t space = blockSize - currentPos;

        void* alignedPtr = static_cast<void*>(currentPtr);
        std::size_t spaceLeft = space;

        if (std::align(alignment, bytes, alignedPtr, spaceLeft)) {
            char* newPtr = static_cast<char*>(alignedPtr);
            std::ptrdiff_t padding = newPtr - currentPtr;
            currentPos += padding + bytes;

            return alignedPtr;
        } else {
            allocateBlock();

            if (bytes > blockSize) {
                char* largeBlock = new char[bytes];
                blocks.push_back(largeBlock);
                // No need to manage alignment as new char[] provides sufficient alignment
                return static_cast<void*>(largeBlock);
            }

            return do_allocate(bytes, alignment);
        }
    }

    void do_deallocate(void* /*p*/, std::size_t /*bytes*/, std::size_t /*alignment*/) override {
        // Arena allocator does not support individual deallocations
        // All memory is freed when the arena is reset or destroyed
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }

private:
    size_t blockSize;
    std::vector<char*> blocks;
    char* currentBlock;
    size_t currentPos;

    void allocateBlock() {
        char* newBlock = new char[blockSize];
        blocks.push_back(newBlock);
        currentBlock = newBlock;
        currentPos = 0;
    }

    Arena(const Arena&) = delete;
    Arena& operator=(const Arena&) = delete;
};
