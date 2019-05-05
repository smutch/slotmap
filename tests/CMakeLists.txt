cmake_minimum_required(VERSION 3.0)
project(slotmap-tests C)

find_path(CMOCKA_INCLUDE_DIR
    NAMES cmocka.h
    PATHS ${CMOCKA_ROOT_DIR}/include
    )

find_library(CMOCKA_LIBRARY
    NAMES cmocka
    PATHS ${CMOCKA_ROOT_DIR}/lib
    )

add_executable(test_stack test_stack.c)
set_property(TARGET test_stack PROPERTY C_STANDARD 99)
target_include_directories(test_stack PRIVATE ${CMOCKA_INCLUDE_DIR} "${CMAKE_SOURCE_DIR}/src")
target_link_libraries(test_stack PRIVATE ${CMOCKA_LIBRARY} slotmap)

add_executable(test_slotmap test_slotmap.c)
set_property(TARGET test_slotmap PROPERTY C_STANDARD 99)
target_include_directories(test_slotmap PRIVATE ${CMOCKA_INCLUDE_DIR} "${CMAKE_SOURCE_DIR}/src")
target_link_libraries(test_slotmap PRIVATE ${CMOCKA_LIBRARY} slotmap)

add_test(stack "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_stack")
add_test(slotmap "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_slotmap")
