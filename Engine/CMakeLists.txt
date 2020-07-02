project( "Engine" )

file( GLOB_RECURSE ENGINE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library( ${PROJECT_NAME} STATIC "${ENGINE_SRC}")

find_package( GLEW CONFIG REQUIRED )
find_package( glfw3 CONFIG REQUIRED )
find_package( glm CONFIG REQUIRED )
find_package( assimp CONFIG REQUIRED )
find_package( spdlog CONFIG REQUIRED )

target_include_directories( ${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/ )
target_link_libraries( ${PROJECT_NAME} GLEW::GLEW glfw glm spdlog::spdlog assimp::assimp )

target_compile_features( ${PROJECT_NAME} PRIVATE cxx_std_17)