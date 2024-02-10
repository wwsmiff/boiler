cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
project(project)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_executable(${PROJECT_NAME})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_sources(${PROJECT_NAME} PRIVATE 
 src/main.c
)
