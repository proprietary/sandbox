#include "arena.hpp"

#include <cassert>
#include <memory>

void* Arena::do_allocate(std::size_t bytes, std::size_t alignment) {
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
