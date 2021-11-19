cmake_minimum_required(VERSION 3.16)
project(Base64pp LANGUAGES CXX)
enable_testing()

# Must compile with C++20, no
# extensions
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_subdirectory(base64pp)
add_subdirectory(tests)

