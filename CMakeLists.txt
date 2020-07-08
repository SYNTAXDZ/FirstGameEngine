cmake_minimum_required(VERSION 3.16)
project( "FirstGameEngine" VERSION 0.1.0 )

include(CTest)
enable_testing()

add_subdirectory( Engine )
add_subdirectory( Sandbox )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
