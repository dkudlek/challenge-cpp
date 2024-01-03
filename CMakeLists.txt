cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(challenge_cpp LANGUAGES CXX)

set(CHALLENGE_CPP_VERSION_MAJOR 0)
set(CHALLENGE_CPP_VERSION_MINOR 1)
set(CHALLENGE_CPP_VERSION_PATCH 0)
set(CHALLENGE_CPP_VERSION
  ${CHALLENGE_CPP_VERSION_MAJOR}.${CHALLENGE_CPP_VERSION_MINOR}.${CHALLENGE_CPP_VERSION_PATCH})

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

# specify the C++ standard
add_library(cpp_compiler_flags INTERFACE)
target_compile_features(cpp_compiler_flags INTERFACE cxx_std_20)

# specify the C standard
add_library(c_compiler_flags INTERFACE)
target_compile_features(c_compiler_flags INTERFACE c_std_90)

# add compiler warning flags just when building this project via
# the BUILD_INTERFACE genex
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(cpp_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)
target_compile_options(c_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

enable_testing()

configure_file(cmake/challenge_cpp_version.h.in ${PROJECT_BINARY_DIR}/challenge_cpp_version.h)

add_subdirectory(source)

install(FILES "${PROJECT_BINARY_DIR}/challenge_cpp_version.h"
  DESTINATION include
)