cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "tiger_lexer")
set(DIR_NAME "lexical_analysis") 
set(INCLUDE_ROOT ../../include)
set(FLEX_SCANNER_BUILD_TARGET flex_build_scanner)
set(FLEX_FILE_NAME "tiger.flex")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")

project(${PROJECT_NAME})

include_directories(${INCLUDE_ROOT}/${DIR_NAME})
file(GLOB PROJECT_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

add_custom_target(${FLEX_SCANNER_BUILD_TARGET}
                    COMMAND flex -o${CMAKE_CURRENT_SOURCE_DIR}/src/lex.yy.c ${CMAKE_CURRENT_SOURCE_DIR}/src/${FLEX_FILE_NAME})
add_executable(${PROJECT_NAME} ${PROJECT_SRC})
add_dependencies(${PROJECT_NAME} ${FLEX_SCANNER_BUILD_TARGET})
