# gfxminimath

Minimal math library for real time 3d graphics using SIMD.

[![Build status](https://ci.appveyor.com/api/projects/status/eq7qvjv1jyrjy40v?svg=true)](https://ci.appveyor.com/project/jimbi-o/gfxminimath)
<!--- TODO configure travis, codecov, coverity -->

## make & build &run

### UNIX like

```
rm -rf build/testgcc9 && cmake -S . -B build/testgcc9 -G Ninja -DCMAKE_C_COMPILER=g++-9 -DCMAKE_CXX_COMPILER=g++-9 -DCMAKE_CXX_COMPILER_LAUNCHER=ccache -DCPM_SOURCE_CACHE=~/dev/.cache/CPM -DBUILD_WITH_TEST=ON && cmake --build build/testgcc9 && ./build/testgcc9/gfxminimath
rm -rf build/testclang11 && cmake -S . -B build/testclang11 -G Ninja -DCMAKE_C_COMPILER=clang-11 -DCMAKE_CXX_COMPILER=clang++-11 -DCMAKE_CXX_COMPILER_LAUNCHER=ccache -DCPM_SOURCE_CACHE=~/dev/.cache/CPM -DBUILD_WITH_TEST=ON -DCMAKE_CXX_FLAGS="-ftime-trace" && cmake --build build/testclang11 && ./build/testgclang11/gfxminimath
```

### Windows

```
cmake -S . -B build/testvs -DBUILD_WITH_TEST=ON && cmake --build build/testvs
build\testvs\Debug\gfxminimath.exe
```
