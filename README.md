# Learn OpenGL

## Summary
Project for me to write (probably messy) OpenGL code for learning modern OpenGL graphics programming.  I am initially following the tutorial here: https://learnopengl.com

## Prerequisites
1. CMake (using 3.19.0) (`brew install cmake`)
2. Conan (using 1.31.3) (`brew install conan`)

## Devlopment Environment
The development environment I am using is as follows:
- Visual Studio Code with the following extensions:
  - C/C++ (ms-vscode.cpptools)
  - CMake Tools (twxs.cmake)
  - CMake (twxs.cmake)
  - Vim (vscodevim.vim)
  - Markdown All in One (yzhang.markdown-all-in-one)

## Conan setup notes
1. `brew install conan`
2. create `conanfile.txt` (see file for details)
3. Note that `build.sh` does the following steps already but the following
   here to document how the project was set up.
4. Do the following (resulting files should not be committed -- they are system specific):
   ```
   mkdir build && cd build
   conan install .. --build=missing
   ```
5. Add the following to CMakeLists.txt:
   ```
   include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
   conan_basic_setup()

   add_executable(myexecutable main.cpp)
   target_link_libraries(myexecutable ${CONAN_LIBS})
   ```
6. Build with cmake as normal (from `build` directory):
   ```
   cmake ..
   cmake --build .
   ```
7. For VSCode: Add `"~/.conan/data/**"` to `.vscode/c_cpp_properties.json` at `configurations[0].["includePath"]` so that VSCode will look for headers in installed conan packages.

## Issue with glfw conan package
As of Nov 21, 2020 the glfw 3.3.2 package would not build for Mac with CMake 3.19.  This issue was fixed in master of glfw in commit 3327050c.  In order to still use conan (and to learn more about it), I copied the conan recipe files for glfw from https://github.com/conan-io/conan-center-index and modified them to build from the above commit of glfw.  These files are under the `patched-dependencies` folder.  In order to get `glfw/3.3.2-3327050c@jkuhn/patched` (as it is referenced in conanfile.txt) into the conan local cache, run the following command in the `patched-dependencies/glfw` directory:
```
conan create . jkuhn/patched
```

## OpenGL Resources:
- [Learn OpenGL](https://learnopengl.com)

## C++ Ecosystem Resources
- [CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
- [Conan Getting Started](https://docs.conan.io/en/latest/getting_started.html)

## Development Environment Resources:
- [Get Started With CMake Tools On Linux](https://code.visualstudio.com/docs/cpp/cmake-linux)
- [Using Clang in VSCode](https://code.visualstudio.com/docs/cpp/config-clang-mac)