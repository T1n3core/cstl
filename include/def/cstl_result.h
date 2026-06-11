#ifndef CSTL_RESULT_H
#define CSTL_RESULT_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief Return value for all API functions of the alloc subsystem that can
 * fail.
 */
typedef enum {
  ALLOC_SUCCESS = 0,
  ALLOC_OUT_OF_MEMORY,
  ALLOC_INVALID_SIZE,
  ALLOC_INVALID_ARENA,
  ALLOC_INVALID_OUT,
  ALLOC_INVALID_STATE,
  ALLOC_INTERNAL_ERROR
} cstl_alloc_result;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !CSTL_RESULT_H
