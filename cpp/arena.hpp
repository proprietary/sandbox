#include <cstddef>
#include <memory_resource>
#include <vector>

class Arena : public std::pmr::memory_resource {
  public:
  explicit Arena(size_t blockSize = 1024 * 1024)  // Default 1MB
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
  void* do_allocate(std::size_t bytes, std::size_t alignment) override;

  void do_deallocate(void* /*p*/, std::size_t /*bytes*/,
                     std::size_t /*alignment*/) override {
    // Arena allocator does not support individual deallocations
    // All memory is freed when the arena is reset or destroyed
  }

  bool do_is_equal(
      const std::pmr::memory_resource& other) const noexcept override {
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
