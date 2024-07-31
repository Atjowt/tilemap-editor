cmake_minimum_required(VERSION 3.0.0)
project(tilemap-editor VERSION 0.1.0 LANGUAGES C)

add_executable(tilemap-editor main.c)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)