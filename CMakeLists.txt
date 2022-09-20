cmake_minimum_required(VERSION 3.15)
project(gfxminimath
  VERSION 1.0
  DESCRIPTION "mini math library for real time 3d graphics"
  LANGUAGES CXX
)

include(cmake/CPM.cmake)
CPMAddPackage("gh:onqtam/doctest#2.4.6")
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
  add_executable(${PROJECT_NAME})
  target_compile_definitions(${PROJECT_NAME} PRIVATE DOCTEST_CONFIG_SUPER_FAST_ASSERTS)
  target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${doctest_SOURCE_DIR}")
  add_subdirectory(tests)
else()
  add_library(${PROJECT_NAME})
endif()

add_subdirectory(src)

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC
  "${vcl_SOURCE_DIR}"
  "${vcladdon_SOURCE_DIR}"
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic>
  $<$<CXX_COMPILER_ID:Clang>:-Weverything -Wno-c++98-c++11-c++14-compat -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-c++20-compat>
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /MP>
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:NOMINMAX>
  VCL_NAMESPACE=vcl
  _USE_MATH_DEFINES
)
target_include_directories(${PROJECT_NAME}
  PUBLIC
  "include"
)
target_precompile_headers(${PROJECT_NAME}
  PUBLIC
  <cmath>
  "${vcl_SOURCE_DIR}/vectorclass.h"
  "${vcl_SOURCE_DIR}/vectormath_exp.h"
  "${vcl_SOURCE_DIR}/vectormath_hyp.h"
  "${vcl_SOURCE_DIR}/vectormath_trig.h"
  "${vcladdon_SOURCE_DIR}/quaternion/quaternion.h"
  "${vcladdon_SOURCE_DIR}/vector3d/vector3d.h"
)

set_directory_properties(PROPERTIES VS_STARTUP_PROJECT gfxminimath)

#cmake -S . -B build/clang13 -G Ninja -DCMAKE_C_COMPILER=clang-13 -DCMAKE_CXX_COMPILER=clang++-13 -DCMAKE_CXX_COMPILER_LAUNCHER=ccache -DCPM_SOURCE_CACHE=~/dev/.cache/CPM -DCMAKE_CXX_FLAGS="-m64 -mavx2"
#cmake.exe -S . -B build/vs -A x64 -DCMAKE_CXX_FLAGS="/arch:AVX2" -DCPM_SOURCE_CACHE=../.cache/CPM
