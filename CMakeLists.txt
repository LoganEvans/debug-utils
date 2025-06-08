cmake_minimum_required(VERSION 3.31)
project(debug-utils VERSION 0.1)
include(CTest)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdiagnostics-color=always")

add_compile_options(-Wno-unused-command-line-argument)
add_link_options(-Wno-unused-command-line-argument)

find_package(fmt CONFIG REQUIRED)

add_library(debug-utils SHARED src/debug.cc)
target_include_directories(
  debug-utils PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_link_libraries(debug-utils PUBLIC fmt::fmt)

add_library(stacktrace-signal-handlers SHARED src/stacktrace-signal-handlers.cc)
target_include_directories(
  stacktrace-signal-handlers
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_link_libraries(stacktrace-signal-handlers PUBLIC cpptrace fmt::fmt)

install(
  TARGETS debug-utils stacktrace-signal-handlers
  EXPORT ${PROJECT_NAME}
  DESTINATION $ENV{out})

install(
  EXPORT ${PROJECT_NAME}
  DESTINATION $ENV{out}/lib/cmake/${PROJECT_NAME}
  FILE ${PROJECT_NAME}-config.cmake
  NAMESPACE theta::)

if(BUILD_TESTING)
  add_subdirectory(test)
endif(BUILD_TESTING)
