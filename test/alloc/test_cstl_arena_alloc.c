#include "../../include/alloc/cstl_arena_alloc.h"
#include "../../lib/Unity/src/unity.h"

static unsigned char buffer[1024];
static cstl_arena arena;

void setUp(void) {
  arena.begin = buffer;
  arena.size = sizeof(buffer);
  arena.used = 0;
}

void test_alloc_null_arena(void) {
  unsigned char *ptr = NULL;

  TEST_ASSERT_EQUAL(ALLOC_INVALID_ARENA, cstl_arena_alloc(NULL, 10, &ptr));
}

void test_alloc_invalid_state(void) {
  arena.used = 2000;

  unsigned char *ptr = NULL;

  TEST_ASSERT_EQUAL(ALLOC_INVALID_STATE, cstl_arena_alloc(&arena, 10, &ptr));
}

void test_alloc_exact_remaining_space(void) {
  arena.used = 1000;

  unsigned char *ptr = NULL;

  TEST_ASSERT_EQUAL(ALLOC_SUCCESS, cstl_arena_alloc(&arena, 24, &ptr));

  TEST_ASSERT_EQUAL_UINT32(1024, arena.used);
}

void test_alloc_one_byte_too_large(void) {
  arena.used = 1000;

  unsigned char *ptr = NULL;

  TEST_ASSERT_EQUAL(ALLOC_OUT_OF_MEMORY, cstl_arena_alloc(&arena, 25, &ptr));
}

void test_alloc_returns_correct_pointer(void) {
  unsigned char *ptr = NULL;

  TEST_ASSERT_EQUAL(ALLOC_SUCCESS, cstl_arena_alloc(&arena, 100, &ptr));

  TEST_ASSERT_EQUAL_PTR(buffer, ptr);
}

void test_alloc_returns_next_region(void) {
  unsigned char *p1;
  unsigned char *p2;

  TEST_ASSERT_EQUAL(ALLOC_SUCCESS, cstl_arena_alloc(&arena, 100, &p1));
  TEST_ASSERT_EQUAL(ALLOC_SUCCESS, cstl_arena_alloc(&arena, 50, &p2));

  TEST_ASSERT_EQUAL_PTR(buffer, p1);
  TEST_ASSERT_EQUAL_PTR(buffer + 100, p2);
}

void test_alloc_increments_used(void) {
  unsigned char *ptr;

  TEST_ASSERT_EQUAL(ALLOC_SUCCESS, cstl_arena_alloc(&arena, 128, &ptr));

  TEST_ASSERT_EQUAL_UINT32(128, arena.used);
}

void test_alloc_multiple_accumulate_used(void) {
  unsigned char *ptr;

  TEST_ASSERT_EQUAL(ALLOC_SUCCESS, cstl_arena_alloc(&arena, 100, &ptr));
  TEST_ASSERT_EQUAL(ALLOC_SUCCESS, cstl_arena_alloc(&arena, 200, &ptr));
  TEST_ASSERT_EQUAL(ALLOC_SUCCESS, cstl_arena_alloc(&arena, 300, &ptr));

  TEST_ASSERT_EQUAL_UINT32(600, arena.used);
}

void test_alloc_zero_size(void) {
  unsigned char *ptr = NULL;

  TEST_ASSERT_EQUAL(ALLOC_INVALID_SIZE, cstl_arena_alloc(&arena, 0, &ptr));

  TEST_ASSERT_EQUAL_UINT32(0, arena.used);
  TEST_ASSERT_NULL(ptr);
}

void test_alloc_after_full_arena(void) {
  unsigned char *ptr;

  TEST_ASSERT_EQUAL(ALLOC_SUCCESS, cstl_arena_alloc(&arena, 1024, &ptr));

  TEST_ASSERT_EQUAL(ALLOC_OUT_OF_MEMORY, cstl_arena_alloc(&arena, 1, &ptr));
}

void test_alloc_failure_does_not_modify_state(void) {
  arena.used = 1000;

  unsigned char *ptr = NULL;

  TEST_ASSERT_EQUAL(ALLOC_OUT_OF_MEMORY, cstl_arena_alloc(&arena, 100, &ptr));

  TEST_ASSERT_EQUAL_UINT32(1000, arena.used);
}

void test_alloc_failure_does_not_touch_pointer(void) {
  unsigned char dummy;
  unsigned char *ptr = &dummy;

  arena.used = 1000;

  TEST_ASSERT_EQUAL(ALLOC_OUT_OF_MEMORY, cstl_arena_alloc(&arena, 100, &ptr));

  TEST_ASSERT_EQUAL_PTR(&dummy, ptr);
}

void test_alloc_null_out(void) {
  TEST_ASSERT_EQUAL(ALLOC_INVALID_OUT, cstl_arena_alloc(&arena, 10, NULL));
}

void test_alloc_zero_size_does_not_modify_state(void) {
  unsigned char *ptr = NULL;

  TEST_ASSERT_EQUAL(ALLOC_INVALID_SIZE, cstl_arena_alloc(&arena, 0, &ptr));

  TEST_ASSERT_EQUAL_UINT32(0, arena.used);
  TEST_ASSERT_NULL(ptr);
}

void test_alloc_exact_fit_keeps_invariant(void) {
  unsigned char *ptr;

  TEST_ASSERT_EQUAL(ALLOC_SUCCESS, cstl_arena_alloc(&arena, arena.size, &ptr));

  TEST_ASSERT_TRUE(arena.used <= arena.size);
}

void tearDown() {}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_alloc_null_arena);
  RUN_TEST(test_alloc_invalid_state);
  RUN_TEST(test_alloc_exact_remaining_space);
  RUN_TEST(test_alloc_one_byte_too_large);
  RUN_TEST(test_alloc_returns_correct_pointer);
  RUN_TEST(test_alloc_returns_next_region);
  RUN_TEST(test_alloc_increments_used);
  RUN_TEST(test_alloc_multiple_accumulate_used);
  RUN_TEST(test_alloc_zero_size);
  RUN_TEST(test_alloc_after_full_arena);
  RUN_TEST(test_alloc_failure_does_not_modify_state);
  RUN_TEST(test_alloc_failure_does_not_touch_pointer);
  RUN_TEST(test_alloc_null_out);
  RUN_TEST(test_alloc_zero_size_does_not_modify_state);
  RUN_TEST(test_alloc_exact_fit_keeps_invariant);

  return UNITY_END();
}
