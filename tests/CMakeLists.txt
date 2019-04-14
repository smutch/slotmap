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

set(TESTS
    test_slotmap.c
    )

add_executable(test_slotmap ${TESTS})
set_property(TARGET test_slotmap PROPERTY C_STANDARD 99)

target_include_directories(test_slotmap PRIVATE ${CMOCKA_INCLUDE_DIR})
target_link_libraries(test_slotmap PRIVATE ${CMOKA_LIBRARY})
