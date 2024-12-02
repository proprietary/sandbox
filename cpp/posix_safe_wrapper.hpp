// RAII-safe wrappers for POSIX I/O.

#ifndef _COM_GITHUB_PROPRIETARY_SANDBOX_CPP_POSIX_SAFE_WRAPPER_INCLUDE_HPP
#define _COM_GITHUB_PROPRIETARY_SANDBOX_CPP_POSIX_SAFE_WRAPPER_INCLUDE_HPP

#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdexcept>
#include <string>

class FileDescriptor {
  public:
  explicit FileDescriptor(int fd) : fd_{fd} {
    if (fd_ < 0) {
      throw std::runtime_error{"Failed to open file descriptor: " +
                               std::string{std::strerror(errno)}};
    }
  }

  ~FileDescriptor() {
    if (fd_ >= 0) {
      ::close(fd_);
    }
  }

  FileDescriptor(const FileDescriptor&) = delete;
  FileDescriptor& operator=(const FileDescriptor&) = delete;

  FileDescriptor(FileDescriptor&& other) noexcept : fd_{other.fd_} {
    other.fd_ = -1;
  }

  FileDescriptor& operator=(FileDescriptor&& other) noexcept {
    if (this != &other) {
      if (fd_ >= 0) {
        ::close(fd_);
      }
      fd_ = other.fd_;
      other.fd_ = -1;
    }
    return *this;
  }

  auto get() -> int { return fd_; }

  private:
  int fd_;
};

class Pipe {
  public:
  Pipe() {
    if (::pipe(pipe_fds_) < 0) {
      throw std::runtime_error{"Pipe creation failed: " +
                               std::string{std::strerror(errno)}};
    }
  }

  ~Pipe() {
    ::close(pipe_fds_[0]);
    ::close(pipe_fds_[1]);
  }

  int read_end() const { return pipe_fds_[0]; }
  int write_end() const { return pipe_fds_[1]; }

  Pipe(const Pipe&) = delete;
  Pipe& operator=(const Pipe&) = delete;

  Pipe(Pipe&& other) noexcept {
    std::memcpy(pipe_fds_, other.pipe_fds_, sizeof(pipe_fds_));
    other.pipe_fds_[0] = -1;
    other.pipe_fds_[1] = -1;
  }

  Pipe& operator=(Pipe&& other) noexcept {
    if (this != &other) {
      ::close(pipe_fds_[0]);
      ::close(pipe_fds_[1]);
      std::memcpy(pipe_fds_, other.pipe_fds_, sizeof(pipe_fds_));
      other.pipe_fds_[0] = -1;
      other.pipe_fds_[1] = -1;
    }
    return *this;
  }

  private:
  int pipe_fds_[2];
};

#endif  // _COM_GITHUB_PROPRIETARY_SANDBOX_CPP_POSIX_SAFE_WRAPPER_INCLUDE_HPP
