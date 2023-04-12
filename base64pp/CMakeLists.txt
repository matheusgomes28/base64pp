set(BASE64PP_SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/base64pp.cpp)

set(BASE64PP_INCLUDE_DIR
  ${CMAKE_CURRENT_LIST_DIR}/include)

if (DEFINED BUILD_SHARED)
    message("Building shared library")
    add_library(base64pp SHARED ${BASE64PP_SOURCES})
else()
    message("Building static library")
    add_library(base64pp base64pp.cpp)
endif()

target_include_directories(base64pp PUBLIC ${BASE64PP_INCLUDE_DIR})

include(GenerateExportHeader)
set(BASE64PP_EXPORT_FILE "${CMAKE_CURRENT_LIST_DIR}/include/base64pp")
generate_export_header(base64pp EXPORT_FILE_NAME "${BASE64PP_INCLUDE_DIR}/base64pp/base64pp_export.h")

