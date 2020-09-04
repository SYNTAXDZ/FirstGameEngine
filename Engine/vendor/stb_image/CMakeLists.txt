cmake_minimum_required( VERSION 3.16.0 )

set( stb_image_SOURCES
  stb_image.cpp
  )

add_library( stb_image STATIC
  "${stb_image_SOURCES}"
  )

set( stb_image_INCLUDES
  "${CMAKE_CURRENT_SOURCE_DIR}"
  )

target_include_directories( stb_image
  PRIVATE
  "${stb_image_INCLUDES}"
  )

set_target_properties( stb_image
  PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${stb_image_INCLUDES}"
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  #LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  #RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  )

