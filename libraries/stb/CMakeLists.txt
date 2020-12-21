cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
cmake_policy(VERSION 3.2)

project(stb_image LANGUAGES C)

add_library(stb_image stb_image.h)

set(CMAKE_CXX_STANDARD 17)

set_target_properties(stb_image PROPERTIES LINKER_LANGUAGE C)

target_compile_definitions(stb_image PRIVATE STB_IMAGE_IMPLEMENTATION)
