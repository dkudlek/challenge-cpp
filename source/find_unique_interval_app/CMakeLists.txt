
add_executable(find_unique_interval_app
  argparse.hpp
  main.cpp
)

target_link_libraries(find_unique_interval_app
  PRIVATE ${PROJECT_NAME}::find_unique_interval cpp_compiler_flags
)

target_include_directories(find_unique_interval_app
  PUBLIC "${PROJECT_BINARY_DIR}" ${state_machine_SOURCE_DIR}
)

add_test(NAME find_unique_interval_app_with_overlap
  COMMAND find_unique_interval_app --naive --dynamic --file ${CMAKE_CURRENT_LIST_DIR}/resources/no_overlapping_intervals.csv)

add_test(NAME find_unique_interval_app_without_overlap
  COMMAND find_unique_interval_app --naive --dynamic --file ${CMAKE_CURRENT_LIST_DIR}/resources/overlapping_intervals.csv)

install(TARGETS find_unique_interval_app DESTINATION bin)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION bin)
