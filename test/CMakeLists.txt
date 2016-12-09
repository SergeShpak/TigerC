cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME tigerc_tests)
set(TESTS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests)
set(TESTED_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../)
set(UNITY_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../Unity/)
set(TESTS_COLLECTION_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

project(${PROJECT_NAME})

MACRO(SUBDIRLIST result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        set(FULL_DIR ${curdir}${child})
        IF(IS_DIRECTORY ${FULL_DIR})
            LIST(APPEND dirlist ${FULL_DIR})
            message("++ DIR found: ${FULL_DIR}")
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

include_directories(${UNITY_ROOT}/include)
file(GLOB UNITY_SRC ${UNITY_ROOT}/src/*.c)

include_directories(${TESTED_ROOT}/include)
file(GLOB TESTED_SRC ${TESTED_ROOT}/src/datatypes/*.c
                    ${TESTED_ROOT}/src/interp_functions/*.c
                    ${TESTED_ROOT}/src/functional_datastructures/*.c)

file(MAKE_DIRECTORY ${TESTS_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TESTS_DIRECTORY})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")
set(TESTS_HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

SUBDIRLIST(SUBDIRS ${TESTS_COLLECTION_DIR}/)

FOREACH(subdir ${SUBDIRS})
    add_subdirectory(${subdir})
ENDFOREACH()
