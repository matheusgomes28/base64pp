include(CTest)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
            "Default build type: Debug" FORCE)
endif()

find_package(GTest REQUIRED)

add_executable(base64pp_tests base64pp_tests.cpp)
target_link_libraries(base64pp_tests PRIVATE base64pp GTest::GTest)

add_test(NAME base64pp_tests COMMAND base64pp_tests)
