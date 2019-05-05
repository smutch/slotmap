cmake_minimum_required(VERSION 3.0)
project(slotmap C)

# output paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# write compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# compile flags
set(CMAKE_C_FLAGS_RELEASE "-O3 -march=native -ffast-math")
set(CMAKE_C_FLAGS_RELEASE "-O0 -fsanitize=memory")

set(SRC
    src/stack.h
    src/stack.c
    src/slotmap.h
    src/slotmap.c
    )

add_library(slotmap STATIC ${SRC})
set_property(TARGET slotmap PROPERTY C_STANDARD 99)


###########
#  TESTS  #
###########

enable_testing()
add_subdirectory(tests)
