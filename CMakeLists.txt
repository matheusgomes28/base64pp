cmake_minimum_required(VERSION 3.16)
project(Base64pp LANGUAGES CXX)

# Must compile with C++20, no
# extensions
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN On)

if(NOT WIN32 AND CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    if (NOT DEFINED CMAKE_INSTALL_PREFIX)
        set(CMAKE_INSTALL_PREFIX "/opt/${PROJECT_NAME}")
    endif()
endif()

option(BUILD_DOCS "Build documentation" Off)
option(BUILD_SHARED "Build shared library" Off)
option(BUILD_TESTS "Build tests with google tests" Off)

add_subdirectory(base64pp)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if (BUILD_DOCS)
    find_package(Doxygen)


    set(DOXYGEN_IN ${CMAKE_CURRENT_LIST_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_LIST_DIR}/Doxyfile)
    set(DOXYGEN_STYLESHEET_DIR "${CMAKE_CURRENT_LIST_DIR}/doxygen-awesome-css")
    set(DOXYGEN_OUTPUT_DIR "${CMAKE_BINARY_DIR}/docs")
    
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    if (DOXYGEN_FOUND)
        # note the option ALL which allows to build the docs together with the application
        add_custom_target(doxygen_build
            COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_LIST_DIR}/Doxyfile"
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)

        file(GLOB DOXYGEN_STYLESHEET_FILES ${CMAKE_CURRENT_LIST_DIR}/doxygen-awesome-css/*.css)
        file(GLOB DOXYGEN_JAVASCRIPT_FILES ${CMAKE_CURRENT_LIST_DIR}/doxygen-awesome-css/*.js)
        add_custom_target(copy_doxygen_css)
        foreach(F ${DOXYGEN_STYLESHEET_FILES})
            get_filename_component(F_NAME ${F} NAME)
            add_custom_command(TARGET copy_doxygen_css
                               POST_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy_if_different ${F} ${DOXYGEN_OUTPUT_DIR}/html/${F_NAME})
        endforeach()
        add_dependencies(doxygen_build copy_doxygen_css)

        add_custom_target(copy_doxygen_js)
        foreach(F ${DOXYGEN_JAVASCRIPT_FILES})
            get_filename_component(F_NAME ${F} NAME)
            add_custom_command(TARGET copy_doxygen_js
                               POST_BUILD
                               COMMAND ${CMAKE_COMMAND} -E copy_if_different ${F} ${DOXYGEN_OUTPUT_DIR}/html/${F_NAME})
        endforeach()
        add_dependencies(doxygen_build copy_doxygen_js)
    else()
        message("Doxygen need to be installed to generate the doxygen documentation")
    endif()
endif()

