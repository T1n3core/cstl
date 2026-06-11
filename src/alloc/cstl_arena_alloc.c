#include "../../include/alloc/cstl_arena_alloc.h"

cstl_alloc_result cstl_arena_create(size_t size, cstl_arena *out) {
  if (!out)
    return ALLOC_INVALID_OUT;

  // TODO: wrap mmap call for testing purposes.
  unsigned char *memory = mmap(NULL, size, PROT_READ | PROT_WRITE,
                               MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (memory == MAP_FAILED)
    switch (errno) {
    case EINVAL:
      return ALLOC_INVALID_SIZE;
    case ENOMEM:
      return ALLOC_OUT_OF_MEMORY;
    default:
      return ALLOC_INTERNAL_ERROR;
    }

  out->begin = memory;
  out->size = size;
  out->used = 0;

  return ALLOC_SUCCESS;
}

cstl_alloc_result cstl_arena_alloc(cstl_arena *arena, size_t size,
                                   unsigned char **out) {
  if (!arena)
    return ALLOC_INVALID_ARENA;

  if (arena->used > arena->size)
    return ALLOC_INVALID_STATE;

  if (size == 0)
    return ALLOC_INVALID_SIZE;

  if (size > arena->size - arena->used)
    return ALLOC_OUT_OF_MEMORY;

  if (!out)
    return ALLOC_INVALID_OUT;

  *out = arena->begin + arena->used;
  arena->used += size;

  return ALLOC_SUCCESS;
}

cstl_alloc_result cstl_arena_free(cstl_arena *arena) {
  if (!arena)
    return ALLOC_INVALID_ARENA;

  if (munmap(arena->begin, arena->size) != 0)
    return ALLOC_INVALID_ARENA;

  arena->begin = NULL;
  arena->used = 0;
  arena->size = 0;

  return ALLOC_SUCCESS;
}

cstl_alloc_result cstl_arena_reset(cstl_arena *arena) {
  if (!arena)
    return ALLOC_INVALID_ARENA;

  arena->used = 0;

  return ALLOC_SUCCESS;
}
