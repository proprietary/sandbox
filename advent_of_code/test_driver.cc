#include <fcntl.h>
#include <gtest/gtest.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "cpp/posix_safe_wrapper.hpp"

namespace {

struct ProcessOutput {
  int exit_code;
  std::string stdout;
};

auto execute_command(std::string command, std::filesystem::path input_file)
    -> ProcessOutput {
  FileDescriptor input_fd{::open(input_file.c_str(), O_RDONLY)};
  Pipe pipe{};
  ::pid_t pid = ::fork();
  if (pid < 0) {
    throw std::runtime_error{"Fork failed: " +
                             std::string{std::strerror(errno)}};
  }
  if (pid == 0) {  // Child process
    // Redirect input file to stdin
    if (::dup2(input_fd.get(), STDIN_FILENO) < 0) {
      throw std::runtime_error{
          "Failed to redirect input to stdin of child process: " +
          std::string{std::strerror(errno)}};
    }
    // Redirect stdout to pipe's write end
    if (::dup2(pipe.write_end(), STDOUT_FILENO) < 0) {
      throw std::runtime_error{"Failed to redirect stdout in child process: " +
                               std::string{std::strerror(errno)}};
    }
    ::close(pipe.read_end());
    // Execute binary
    char* const args[] = {const_cast<char*>(command.c_str()), nullptr};
    if (::execvp(command.c_str(), args) < 0) {
      throw std::runtime_error{"Failed to execute command: " +
                               std::string{std::strerror(errno)}};
    }
  }
  // Parent process
  ::close(pipe.write_end());

  std::ostringstream output_stream;
  char buffer[4096];
  ssize_t bytes_read;
  while ((bytes_read = ::read(pipe.read_end(), buffer, sizeof(buffer))) > 0) {
    output_stream.write(buffer, bytes_read);
  }

  int status;
  ::waitpid(pid, &status, 0);
  return ProcessOutput{
      .exit_code = status,
      .stdout = output_stream.str(),
  };
}

TEST(AdventOfCode, CompareOutputs) {
  char* const executable = std::getenv("AOC_EXECUTABLE");
  char* const input_file = std::getenv("AOC_INPUT_FILE");
  char* const expected_output_file = std::getenv("AOC_OUTPUT_FILE");

  ASSERT_NE(executable, nullptr);
  ASSERT_NE(input_file, nullptr);
  ASSERT_NE(expected_output_file, nullptr);

  std::filesystem::path input_file_path{input_file};
  ASSERT_TRUE(std::filesystem::exists(input_file_path));

  std::filesystem::path expected_output_path{expected_output_file};
  ASSERT_TRUE(std::filesystem::exists(expected_output_path));

  std::string expected_output;
  {
    std::ifstream is{expected_output_path};
    ASSERT_TRUE(is.is_open())
        << "Failed to open file with expected output: " << expected_output_path;
    std::stringstream expected_output_buffer;
    expected_output_buffer << is.rdbuf();
    expected_output = expected_output_buffer.str();
  }

  const auto actual_output = execute_command(executable, input_file_path);
  // EXPECT_EQ(actual_output.exit_code, 0);
  EXPECT_EQ(actual_output.stdout, expected_output);
}

}  // namespace
