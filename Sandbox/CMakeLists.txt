project( "Sandbox" )

file( GLOB SANDBOX_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable( ${PROJECT_NAME} ${SANDBOX_SRC} )

target_link_libraries( ${PROJECT_NAME} Engine )
