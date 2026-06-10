/**
 * @file cstl_arena_alloc.h
 * @brief Arena allocator.
 * @note No alignment support.
 */

#ifndef CSTL_ARENA_ALLOC_H
#define CSTL_ARENA_ALLOC_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "../def/cstl_result.h"
#include "../def/macros.h"
#include <errno.h>
#include <stddef.h>
#include <sys/mman.h>

#define ARENA_LARGE_SIZE 16777216
#define ARENA_MEDIUM_SIZE 1048576
#define ARENA_SMALL_SIZE 32768

/**
 * @brief Pool of raw memory for allocation.
 */
typedef struct {
  unsigned char *begin;
  size_t used;
  size_t size;
} cstl_arena;

/**
 * @brief Creates an arena with the mmap syscall.
 * @return Result enum indicating operation success.
 */
WARN_UNUSED
cstl_alloc_result cstl_arena_create(size_t size, cstl_arena *out);

/**
 * @brief Allocates memory from an arena.
 * @param arena The arena from which memory will be taken.
 * @param size Amount of bytes to allocate.
 * @param out Pointer to the allocated memory.
 * @return Result enum indicating operation success.
 */
WARN_UNUSED
cstl_alloc_result cstl_arena_alloc(cstl_arena *arena, size_t size,
                                   unsigned char **out);

/**
 * @brief Frees the entire arena with munmap syscall.
 * @param arena The arena to free.
 * @return Result enum indicating operation success.
 */
WARN_UNUSED
cstl_alloc_result cstl_arena_free(cstl_arena *arena);

/**
 * @brief Frees the entire arena but lets you reuse it.
 * @param arena The arena to free.
 * @return Result enum indicating operation success.
 */
WARN_UNUSED
cstl_alloc_result cstl_arena_reset(cstl_arena *arena);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !CSTL_ARENA_ALLOC_H
