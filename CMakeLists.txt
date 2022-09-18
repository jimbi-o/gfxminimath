cmake_minimum_required(VERSION 3.15)
project(gfxminimath
  VERSION 1.0
  DESCRIPTION "mini math library for real time 3d graphics"
  LANGUAGES CXX
)

include(cmake/CPM.cmake)
CPMAddPackage(
  NAME vcl
  GITHUB_REPOSITORY "vectorclass/version2"
  VERSION 2.02.00
  DOWNLOAD_ONLY yes
)
CPMAddPackage(
  NAME vcladdon
  GITHUB_REPOSITORY "vectorclass/add-on"
  GIT_TAG "a48a87517f1a6abad67e4231d22a84849075aab7"
  DOWNLOAD_ONLY yes
)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  add_executable(${CMAKE_PROJECT_NAME})
  CPMAddPackage("gh:onqtam/doctest#2.4.6")
  target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE BUILD_WITH_TEST DOCTEST_CONFIG_SUPER_FAST_ASSERTS)
  target_include_directories(${CMAKE_PROJECT_NAME} SYSTEM PUBLIC "${doctest_SOURCE_DIR}")
  add_subdirectory(tests)
else()
  add_library(${CMAKE_PROJECT_NAME})
endif()

target_include_directories(${CMAKE_PROJECT_NAME} SYSTEM PUBLIC
  "${vcl_SOURCE_DIR}"
  "${vcladdon_SOURCE_DIR}"
)

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

#cmake -S . -B build/clang13 -G Ninja -DCMAKE_C_COMPILER=clang-13 -DCMAKE_CXX_COMPILER=clang++-13 -DCMAKE_CXX_COMPILER_LAUNCHER=ccache -DCPM_SOURCE_CACHE=~/dev/.cache/CPM -DCMAKE_CXX_FLAGS="-m64 -mavx2"
