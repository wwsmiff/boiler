cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
project(boiler)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(USER_HOME $ENV{HOME})
add_executable(${PROJECT_NAME})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_sources(${PROJECT_NAME} PRIVATE 
 src/main.cpp
 src/boiler.cpp
)

install(TARGETS boiler DESTINATION "${USER_HOME}/.boiler/bin")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/boilerplates" DESTINATION "${USER_HOME}/.boiler")
