# advent-of-code-2023

Advent of Code 2023 solutions in C++.

Some days I used **cmake** on Linux, and other days I used Visual Studio on Windows.

If a day's folder contains a `*.sln` file, then I used Visual Studio. Double click on that file in Windows
to get started.

If a day's folder contains a `CMakeLists.txt` file, then I used **cmake**.  Get started by:

1. Install a C++ compiler, **cmake**, and [vcpkg](https://github.com/microsoft/vcpkg)
2. Change into a day's directory.
3. Run `cmake -B [build directory] -S . -DCMAKE_TOOLCHAIN_FILE="[path to vcpkg]/scripts/buildsystems/vcpkg.cmake"`.
   Common choices for `[build directory]` are `build` or `out`. **cmake** will create the directory if it doesn't exist.
4. Run `cmake --build [build directory]`
5. Run the executables in `[build directory]`. Make sure the `*.txt` input files can be found.
