cmake_minimum_required(VERSION 3.15)
project(gfxminimath
  VERSION 1.0
  DESCRIPTION "mini math library for real time 3d graphics"
  LANGUAGES CXX
)

include(cmake/CPM.cmake)
CPMAddPackage("gh:onqtam/doctest#2.4.6")

option(BUILD_WITH_TEST "build project with tests" OFF)
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  add_executable(${CMAKE_PROJECT_NAME})
  if (BUILD_WITH_TEST)
	  target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE BUILD_WITH_TEST DOCTEST_CONFIG_SUPER_FAST_ASSERTS)
	  target_include_directories(${CMAKE_PROJECT_NAME} SYSTEM PUBLIC "${doctest_SOURCE_DIR}")
	  add_subdirectory(tests)
  else()
	  add_subdirectory(app)
  endif()
else()
  add_library(${CMAKE_PROJECT_NAME})
endif()

target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic>
  $<$<CXX_COMPILER_ID:Clang>:-Weverything -Wno-c++98-c++11-c++14-compat -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-c++20-compat>
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /MP>
)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:NOMINMAX>)
target_include_directories(${CMAKE_PROJECT_NAME}
  PUBLIC
  "include"
)
add_subdirectory(src)
