#include <fmt/format.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <array>
#include <cpptrace/cpptrace.hpp>
#include <csignal>

namespace {
struct CpptraceSignalHandler {
  CpptraceSignalHandler() {
    for (const auto sig :
         std::to_array({SIGABRT, SIGFPE, SIGILL, SIGINT, SIGSEGV, SIGTERM})) {
      std::signal(SIGSEGV, signal_handler);
    }
  }

  static void signal_handler(int signal) {
    fmt::print(stderr, "Caught signal: {}\n", signal);
    cpptrace::generate_trace().print();
    std::exit(signal);
  }
};
CpptraceSignalHandler cpptrace_signal_handler{};
}  // namespace

using ::testing::Eq;

namespace theta::debug_utils {

TEST(DebugTest, foo) { EXPECT_THAT(1, Eq(1)); }

TEST(DebugTest, throw) { raise(SIGSEGV); }

}  // namespace theta::debug_utils
