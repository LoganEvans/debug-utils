find_package(cpptrace REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(debug-utils-test debug-utils-test.cc)
target_link_libraries(
  debug-utils-test PRIVATE cpptrace::cpptrace GTest::gmock GTest::gtest_main
                           debug-utils stacktrace-signal-handlers fmt)
gtest_discover_tests(debug-utils-test)

install(
  TARGETS debug-utils-test
  EXPORT ${PROJECT_NAME}
  DESTINATION $ENV{out}/bin/test)
