cmake_minimum_required(VERSION 3.1)

project(
  ra-test
  VERSION 1.0
  LANGUAGES CXX)

set(ra_test_includes
  ${CMAKE_CURRENT_LIST_DIR}/include/)

set(alg_lib_srcs
  ${CMAKE_CURRENT_LIST_DIR}/lib/alg.cc)

set(alg_lib_includes
  ${CMAKE_CURRENT_LIST_DIR}/include/)

add_library(alg_lib STATIC ${alg_lib_srcs})
set_property(TARGET alg_lib PROPERTY CXX_STANDARD 17)
target_include_directories(alg_lib PRIVATE ${alg_lib_includes})

macro(ra_test_add target_name)
  add_executable(${target_name} ${CMAKE_CURRENT_LIST_DIR}/test/test.${target_name}.cc)
  set_property(TARGET ${target_name} PROPERTY CXX_STANDARD 17)
  target_include_directories(${target_name} PRIVATE ${ra_test_includes})
  target_link_libraries(${target_name} PRIVATE alg_lib)
endmacro()

macro(ra_algorithm_add target_name)
  add_executable(${target_name} ${CMAKE_CURRENT_LIST_DIR}/src/alg.${target_name}.cc)
  set_property(TARGET ${target_name} PROPERTY CXX_STANDARD 17)
  target_include_directories(${target_name} PRIVATE ${ra_test_includes})
  target_link_libraries(${target_name} PRIVATE alg_lib)
endmacro()

ra_test_add(hello)
ra_algorithm_add(binary_search)
ra_algorithm_add(bag)
ra_algorithm_add(queue)
ra_algorithm_add(stack)
ra_algorithm_add(dijkstra_two_stack)
