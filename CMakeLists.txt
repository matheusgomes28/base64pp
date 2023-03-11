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


option(BUILD_DOCS "Build documentation" ON)

if (BUILD_DOCS)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        # note the option ALL which allows to build the docs together with the application
        add_custom_target(doxygen_build
            COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_LIST_DIR}/Doxyfile"
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
    else()
        message("Doxygen need to be installed to generate the doxygen documentation")
    endif()
endif()

