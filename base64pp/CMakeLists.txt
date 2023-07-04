set(BASE64PP_SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/base64pp.cpp)

set(BASE64PP_INCLUDE_DIR
  ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(base64pp base64pp.cpp)

target_include_directories(base64pp PUBLIC ${BASE64PP_INCLUDE_DIR})

include(GenerateExportHeader)
set(BASE64PP_EXPORT_FILE "${CMAKE_CURRENT_LIST_DIR}/include/base64pp")
generate_export_header(base64pp EXPORT_FILE_NAME "${BASE64PP_INCLUDE_DIR}/base64pp/base64pp_export.h")

file(GLOB BASE64PP_PUBLIC_HEADERS ${BASE64PP_INCLUDE_DIR}/**/*.h)
set_target_properties(base64pp
  PROPERTIES PUBLIC_HEADER "${BASE64PP_PUBLIC_HEADERS}")

include(GNUInstallDirs)
install(TARGETS base64pp)

# Generate PKG-Config
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/base64pp.pc.in" "${CMAKE_CURRENT_BINARY_DIR}/base64pp.pc" @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/base64pp.pc" DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
