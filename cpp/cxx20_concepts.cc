#include <__concepts/arithmetic.h>
#include <__concepts/convertible_to.h>
#include <unistd.h>

#include <concepts>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

// Using Concepts for overload resolution

void process(auto v) { std::cout << "process()\n"; }

void process(std::integral auto value) {
  std::cout << "process(integral): " << value << "\n";
}

void process(std::floating_point auto value) {
  std::cout << "process(floating point): " << value << "\n";
}

// Using ad-hoc concepts

class MyFileReader {
  private:
  std::vector<uint8_t> buffer_;
  FILE *file_;

  public:
  MyFileReader(const char *filename) : file_(std::fopen(filename, "rb")) {}
  ~MyFileReader() {
    if (file_ != nullptr) std::fclose(file_);
  }
  MyFileReader(const MyFileReader &) = delete;
  MyFileReader &operator=(const MyFileReader &) = delete;
  MyFileReader(MyFileReader &&other)
      : buffer_(std::move(other.buffer_)), file_(other.file_) {
    other.file_ = nullptr;
  }
  MyFileReader &operator=(MyFileReader &&other) {
    buffer_ = std::move(other.buffer_);
    file_ = other.file_;
    other.file_ = nullptr;
    return *this;
  }

  auto read(size_t n_bytes) -> size_t {
    buffer_.resize(buffer_.size() + n_bytes);
    return std::fread(buffer_.data(), 1, n_bytes, file_);
  }

  auto get_buffer() -> std::vector<uint8_t> & { return buffer_; }
};

// Using concepts to constrain a function template

template <typename T>
void read_full_file(T &&reader)
  requires requires(T reader, size_t n) {
    { reader.read(n) } -> std::same_as<std::size_t>;
  }
{
  constexpr size_t CHUNK_SIZE = 65536;
  while (true) {
    size_t n = reader.read(CHUNK_SIZE);
    if (n == 0) {
      break;
    }
  }
}

struct TempFileWriter {
  int fd_;
  std::string filename_;
  TempFileWriter() {
    filename_ = "/tmp/tempfile.XXXXXX";
    fd_ = ::mkstemp(filename_.data());
    if (fd_ == -1) {
      std::cerr << "Cannot create temporary file " << ::strerror(errno) << "\n";
      throw std::runtime_error("Cannot create temporary file");
    }
  }
  ~TempFileWriter() {
    if (fd_ != -1) {
      ::close(fd_);
      ::unlink(filename_.c_str());
    }
  }
  TempFileWriter(const TempFileWriter &) = delete;
  TempFileWriter &operator=(const TempFileWriter &) = delete;
  TempFileWriter(TempFileWriter &&other)
      : fd_(other.fd_), filename_(std::move(other.filename_)) {
    other.fd_ = -1;
  }
  TempFileWriter &operator=(TempFileWriter &&other) {
    fd_ = other.fd_;
    filename_ = std::move(other.filename_);
    return *this;
  }
  auto write(const std::vector<uint8_t> &buffer) -> size_t {
    return ::write(fd_, buffer.data(), buffer.size());
  }
  auto write(std::string_view str) -> size_t {
    return ::write(fd_, str.data(), str.size());
  }
  auto get_filename() -> const char * { return filename_.c_str(); }
};

int main(int argc, char **argv) {
  process("the meaning of life");
  process(42);
  process(42.18);
  TempFileWriter writer;
  writer.write("Hello, World!\n");
  std::cout << "Created temporary file at: " << writer.get_filename() << "\n";
  MyFileReader reader(writer.get_filename());
  read_full_file(reader);
  std::cout << "Read " << reader.get_buffer().size() << " bytes\n";
  std::cout << "Contents: "
            << std::string(reader.get_buffer().begin(),
                           reader.get_buffer().end())
            << "\n";
  return 0;
}
