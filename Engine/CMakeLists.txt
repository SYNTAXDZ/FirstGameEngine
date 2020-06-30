project( "Engine" )

add_library( ${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/FGE/Core/Application.cpp)

find_package( GLEW CONFIG REQUIRED )
find_package( glfw3 CONFIG REQUIRED )
find_package( glm CONFIG REQUIRED )
find_package( assimp CONFIG REQUIRED )
find_package( spdlog CONFIG REQUIRED )

target_include_directories( ${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/ )
target_link_libraries( ${PROJECT_NAME} GLEW::GLEW glfw glm spdlog::spdlog assimp::assimp )
