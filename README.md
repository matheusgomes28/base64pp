[![Build Status](https://dev.azure.com/Matheusgarcia28/Base64pp/_apis/build/status%2Fmatheusgomes28.base64pp?branchName=main)](https://dev.azure.com/Matheusgarcia28/Base64pp/_build/latest?definitionId=3&branchName=main) | [![codecov](https://codecov.io/github/matheusgomes28/base64pp/branch/main/graph/badge.svg?token=5Q5G5MNFLO)](https://codecov.io/github/matheusgomes28/base64pp)
|---|----|

# Base64pp - A Modern C++ Implementation Of Base64 Encoding

This project was created for a post on my personal blog
where I explain [how to implement a Base64 encoder](https://matgomes.com/base64-encode-decode-cpp/)
using C++ code.


## Project Dependencies

Base64pp doesn't rely on any third-party libraries per se,
but the unit tests were implemented with GTest. However,
the dependencies were managed with [Conan](https://conan.io)
so you do need to install that first.

Regarding the build system, this project requires a farily
recent version of CMake. In addition, your favourite compiler
also needs to support C++20. For more information, visit the
Base64 encoding with C++ post.

## Building The Project

Building from the command line is fairly simple. In this section,
we're assuming you're on a bash-like terminal, with CMake
and Conan accessible. For building on IDE environments, 
please see the later sections (Visual Studio and Clion).

Firstly, create a `build` directory where all the Conan and
build files will be stored:

```bash
cd ${PROJECT_ROOT_DIR}
mkdir build && cd build
``` 

**Note** that `${PROJECT_ROOT_DIR}` is the path to the directory
where this git repository was cloned to.

Following that, simply install the Conan dependencies:

```bash
conan install --build=missing ..
```

**Note:** if Conan did not properly identify your build profile,
specify the `compiler`, `compiler.libcxx`, `build_type` and
`architecture` to the above with the `-s` flags. [Find out more
about the settings in this page](https://docs.conan.io/en/latest/reference/commands/consumer/install.html#settings).

With all the CMake `Find*.cmake` files installed under `build/`
by Conan, we can simply configure and build with CMake:

```bash
cmake -DCMAKE_MODULE_PATH="$(pwd)" ..

cmake --build . -j${N_PROCS}      
```
That's it! You should now have the project fully built under
the `build/` directory. **Note** that we're assumed you're
running these commands from `build/`, and `${N_PROCS}` is
the number of cores available in your machine.

### Integrating The Build With Clion

To integrate with CLion, simply open the root directory 
of the project with CLion (where the main `CMakeLists.txt`
is located).

If you have followed the Conan installation steps above,
you should have a bunch of `Find*.cmake` files in the
`build/` directory. For CLion's integrated CMake to
configure the project, you need to provie the **absolute
path** to `build/`. To achieve this, add

```bash
-DCMAKE_MODULE_PATH="/some/path/to/base64pp/build"
``` 

Under *Settings -> Build, Execution, Deployment -> CMake*,
in the "Cmake Options" textbox. After saving these changes,
CLion should fully configure the project and building /
debugging be available.

### Integrating With Visual Studio

Similar to the CLion integration, open the root directory
containing the `CMakeLists.txt`, then add the following
CMake variables to your [build configuration's
`CMakeSettings.json`](https://docs.microsoft.com/en-us/cpp/build/cmakesettings-reference?view=msvc-170):

```json
"variables": [
    {
      "name": "CMAKE_MODULE_PATH",
      "value": "path/to/base64pp/build",
      "type": "FILEPATH"
    }
  ]
```

After that, reload the CMake and you're good to go.

## Learn How Base64 Works

If you're interested in finding out how this
implementation works and how it came about, please read
the post I made on [how to Base64 encode and decode
with C++](https://matgomes.com/base64-encode-decode-cpp/).

If you have any questions, suggestions or feedback,
either create a PR or feel free to drop a comment in the
post!







