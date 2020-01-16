cmake_minimum_required(VERSION 3.15)
project(JsonParser C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(libft)

include_directories(include)

include_directories(libft_INCLUDE_DIRS)
aux_source_directory(src src)

add_executable(JsonParser ${src})

target_link_libraries(JsonParser libft)

add_library(jsonparser ${src})