find_package(GTest REQUIRED)

add_executable(find_unique_interval_test test.cpp)

target_link_libraries(find_unique_interval_test ${PROJECT_NAME}::find_unique_interval GTest::GTest GTest::Main)
target_include_directories(
  find_unique_interval_test PUBLIC "${PROJECT_BINARY_DIR}" ${find_unique_interval_SOURCE_DIR}
)
gtest_add_tests(TARGET find_unique_interval_test
                TEST_SUFFIX .noArgs
                TEST_LIST   noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 10)
