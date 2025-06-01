#include <fmt/format.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "theta/debug-utils/debug.h"

using ::testing::Eq;

namespace theta::debug_utils {

TEST(DebugTest, foo) { EXPECT_THAT(1, Eq(1)); }

TEST(DebugTest, throw) { raise(SIGSEGV); }

}  // namespace theta::debug_utils
