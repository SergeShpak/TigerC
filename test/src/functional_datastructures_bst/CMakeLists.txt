file (GLOB TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

include_directories(${TESTS_HEADERS_DIR}/functional_datastructures)

get_filename_component(PROJECT_ID ${CMAKE_CURRENT_SOURCE_DIR} NAME)
add_executable(${PROJECT_ID} ${TESTED_SRC} ${UNITY_SRC} ${TEST_SRC})
