cmake_minimum_required(VERSION 3.16)
project( "FirstGameEngine" VERSION 0.1.0 )

include(CTest)
enable_testing()

# SET (CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE STRING "C++ compiler" FORCE)

#set(CMAKE_CXX_CLANG_TIDY
#  clang-tidy;
#  -header-filter=.;
#  -checks=*;)


add_subdirectory( Engine )
add_subdirectory( Sandbox )

# set( CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Engine/vendor/vcpkg/scripts/buildsystems/vcpkg.cmake
    #  CACHE STRING "Vcpkg toolchain file" )
# set( CMAKE_C_COMPILER "/usr/bin/clang" )
# set( CMAKE_CXX_COMPILER "/usr/bin/clang++" )
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
