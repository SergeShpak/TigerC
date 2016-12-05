cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME tigerc_tests)
set(TESTS_DIRECTORY tests)
set(TESTED_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../)
set(UNITY_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../Unity/)

project(${PROJECT_NAME})

include_directories(${UNITY_ROOT}/include)
file(GLOB UNITY_SRC ${UNITY_ROOT}/src/*.c)

include_directories(${TESTED_ROOT}/include)
file(GLOB TESTED_SRC ${TESTED_ROOT}/src/datatypes/*.c
                    ${TESTED_ROOT}/src/interp_functions/*.c
                    ${TESTED_ROOT}/src/functional_datastructures/*.c)

file(GLOB TESTS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

file(MAKE_DIRECTORY ${TESTS_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TESTS_DIRECTORY})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")
message("++ ${CMAKE_C_FLAGS}")
message("++ ${CMAKE_CXX_FLAGS}")

FOREACH(TEST_FILE_NAME ${TESTS_SRC})
    get_filename_component(EXE_NAME ${TEST_FILE_NAME} NAME_WE)
    add_executable(${EXE_NAME} ${TESTED_SRC} ${UNITY_SRC} ${TEST_FILE_NAME})
ENDFOREACH(TEST_FILE_NAME)
