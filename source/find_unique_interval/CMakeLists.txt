add_library(find_unique_interval find_unique_interval.h find_unique_interval.cpp)
add_library(${PROJECT_NAME}::find_unique_interval ALIAS find_unique_interval)

target_include_directories(find_unique_interval
                           INTERFACE 
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                           $<INSTALL_INTERFACE:include>
                           )
target_link_libraries(find_unique_interval PUBLIC cpp_compiler_flags)

if(${BUILD_SHARED_LIBS})
  target_compile_definitions(find_unique_interval PRIVATE "EXPORTING_STATE_MACHINE")
  target_compile_definitions(find_unique_interval PRIVATE "BUILD_SHARED")
endif()
set_target_properties(find_unique_interval PROPERTIES PUBLIC_HEADER "${HEADER_FILES}")


install(
  TARGETS find_unique_interval cpp_compiler_flags
  EXPORT find_unique_interval_targets
  DESTINATION lib)
install(FILES find_unique_interval.h DESTINATION include/find_unique_interval)

include(CMakePackageConfigHelpers)

# generate the config file that includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/find_unique_interval-config.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}__find_unique_interval-config.cmake"
  INSTALL_DESTINATION "lib/cmake"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}__find_unique_interval-config.cmake
  DESTINATION cmake
  )

install(EXPORT find_unique_interval_targets
  FILE ${PROJECT_NAME}__find_unique_interval.cmake
  NAMESPACE ${PROJECT_NAME}:: 
  DESTINATION cmake
  )

add_subdirectory(tests)