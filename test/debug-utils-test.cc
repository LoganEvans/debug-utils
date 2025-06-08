#include <fmt/format.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "theta/debug-utils/debug.h"

using ::testing::Eq;

namespace theta::debug_utils {

TEST(DebugTest, foo) { EXPECT_THAT(1, Eq(1)); }

TEST(DebugTest, DISABLED_stacktraceOnSignal) { raise(SIGINT); }

TEST(DebugTest, DISABLED_spinForever) {
  // This is to check that
  // $ kill -s SIGUSR1 <PID>
  // properly prints a stack trace and continues spinning.
  fmt::print("> spinForever\n");
  while (1);
}

}  // namespace theta::debug_utils
