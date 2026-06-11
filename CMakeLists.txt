cmake_minimum_required(VERSION 3.20)

project(cstl C)

enable_testing()

target_compile_options(cstl PRIVATE -Wall -Wextra -Werror)

add_library(cstl src/alloc/cstl_arena_alloc.c)
add_library(unity lib/Unity/src/unity.c)

target_include_directories(unity PUBLIC lib/Unity/src)
target_include_directories(cstl PUBLIC include)

add_executable(test_arena_alloc test/alloc/test_cstl_arena_alloc.c)

add_test(NAME arena_alloc COMMAND test_arena_alloc)

target_link_libraries(test_arena_alloc PRIVATE cstl unity)
