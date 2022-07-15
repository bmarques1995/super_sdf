cmake_minimum_required(VERSION 3.20)

project(Textures LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(./vendor/glfw)
add_subdirectory(./vendor/glad)

file(GLOB_RECURSE STANDALONE_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/app/*.cc")
file(GLOB_RECURSE STANDALONE_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/app/*.hh")

file(GLOB_RECURSE V_SHAD RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "assets/shaders/*.vs.glsl")
file(GLOB_RECURSE F_SHAD RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "assets/shaders/*.fs.glsl")
file(GLOB_RECURSE PROJ_TEX RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "assets/textures/*.jpg")

add_executable(super_sdf_standalone ${STANDALONE_SOURCES} ${STANDALONE_HEADERS})

foreach(vertex IN LISTS V_SHAD F_SHAD)
    file(COPY ${vertex} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/shaders)
endforeach()

foreach(vertex IN LISTS PROJ_TEX)
    file(COPY ${vertex} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/textures)
endforeach()

target_include_directories(super_sdf_standalone PRIVATE ./vendor/glfw/include ./vendor/glad/include ./vendor/stb ./src/app)
target_link_libraries(super_sdf_standalone PRIVATE glfw glad)