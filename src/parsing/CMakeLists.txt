cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "tiger_parser")
set(DIR_NAME "parsing") 
set(INCLUDE_ROOT ../../include)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")

project(${PROJECT_NAME})

include_directories(${INCLUDE_ROOT}/${DIR_NAME})
file(GLOB PROJECT_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

add_executable(${PROJECT_NAME} ${PROJECT_SRC})
