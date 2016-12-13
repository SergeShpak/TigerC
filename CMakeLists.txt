cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME tigerc)

project(${PROJECT_NAME})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")

set(INCLUDE_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB PROJECT_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/datatypes/*.c
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/interp_functions/*.c)

add_executable(${PROJECT_NAME} ${PROJECT_SRC} ${UNITY_SRC})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/lexical_analysis)
