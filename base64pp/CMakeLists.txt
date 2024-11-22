set(BASE64PP_SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/base64pp.cpp)

set(BASE64PP_INCLUDE_DIR
  ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(base64pp)
target_sources(base64pp
  PUBLIC
    FILE_SET CXX_MODULES FILES
      base64pp.cpp
)

# Extra modules stuff
target_include_directories(base64pp PUBLIC ${BASE64PP_INCLUDE_DIR})

include(GNUInstallDirs)
install(TARGETS base64pp)

# Generate PKG-Config
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/base64pp.pc.in" "${CMAKE_CURRENT_BINARY_DIR}/base64pp.pc" @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/base64pp.pc" DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")

