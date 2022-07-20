cmake_minimum_required(VERSION 3.20)

project(super_sdf LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(./vendor/glfw)
add_subdirectory(./vendor/glad)

file(GLOB_RECURSE SUPER_SDF_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/api/*.cc")
file(GLOB_RECURSE SUPER_SDF_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/api/*.hh")

file(GLOB_RECURSE STANDALONE_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/app/*.cc")
file(GLOB_RECURSE STANDALONE_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/app/*.hh")

file(GLOB_RECURSE V_SHAD RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "assets/shaders/*.vs.glsl")
file(GLOB_RECURSE F_SHAD RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "assets/shaders/*.fs.glsl")
file(GLOB_RECURSE PROJ_TEX RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "assets/images/*.jpg")
file(GLOB_RECURSE PROJ_TTF RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "assets/fonts/*.ttf")
file(GLOB_RECURSE PROJ_OTF RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "assets/fonts/*.otf")

add_library(super_sdf ${SUPER_SDF_SOURCES} ${SUPER_SDF_HEADERS})
target_include_directories(super_sdf PUBLIC ./src/api/include ./vendor/stb ./vendor/eigen3)

add_executable(super_sdf_standalone ${STANDALONE_SOURCES} ${STANDALONE_HEADERS})
target_include_directories(super_sdf_standalone PRIVATE ./vendor/glfw/include ./vendor/glad/include ./src/app ./src/api/include)
target_link_libraries(super_sdf_standalone PRIVATE glfw glad super_sdf)

foreach(vertex IN LISTS V_SHAD F_SHAD)
    file(COPY ${vertex} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/shaders)
endforeach()

foreach(image IN LISTS PROJ_TEX)
    file(COPY ${image} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/images)
endforeach()

foreach(font IN LISTS PROJ_TTF PROJ_OTF)
    file(COPY ${font} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/fonts)
endforeach()
