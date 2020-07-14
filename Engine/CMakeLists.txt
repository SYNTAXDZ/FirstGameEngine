cmake_minimum_required( VERSION 3.16 )
project( "Engine" VERSION 1.0.1 DESCRIPTION "My FirstGameEngine" )

file( GLOB_RECURSE ENGINE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library( ${PROJECT_NAME} STATIC "${ENGINE_SRC}")

add_subdirectory( vendor/imgui )

find_package( GLEW CONFIG REQUIRED )
find_package( glfw3 CONFIG REQUIRED )
find_package( glm CONFIG REQUIRED )
find_package( assimp CONFIG REQUIRED )
find_package( spdlog CONFIG REQUIRED )

target_include_directories( ${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/ )
target_link_libraries( ${PROJECT_NAME} GLEW::GLEW glfw glm spdlog::spdlog assimp::assimp ImGui )


set_target_properties(${PROJECT_NAME} PROPERTIES UNITY_BUILD ON)

set_target_properties( "Engine" PROPERTIES VERSION ${PROJECT_VERSION} )
set_target_properties( "Engine" PROPERTIES SOVERSION 1 )

target_compile_features( ${PROJECT_NAME} PRIVATE cxx_std_17)
add_compile_definitions( GLFW_INCLUDE_NONE )

# the pch will be included automaticlly in all cpp files in this target
target_precompile_headers( ${PROJECT_NAME}
                           PUBLIC  
                           [["precompiled.h"]])