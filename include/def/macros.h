#ifndef MACROS_H
#define MACROS_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#if defined(__GNUC__) || defined(__clang__)

#define NONNULL(...) __attribute__((nonnull(__VA_ARGS__)))
#define PURE __attribute__((pure))
#define WARN_UNUSED __attribute__((warn_unused_result))
#define NORETURN __attribute__((noreturn))
#define UNUSED __attribute__((unused))
#define CONST_FN __attribute__((const))
#define LIKELY(x) __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)
#define HOT __attribute__((hot))
#define COLD __attribute__((cold))
#define ALWAYS_INLINE inline __attribute__((always_inline))
#define ALIGN(n) __attribute__((aligned(n)))
#define PACKED __attribute__((packed))
#define PRINTF_LIKE(fmt, args) __attribute__((format(printf, fmt, args)))

#elif defined(_MSC_VER)

#define NONNULL(...)
#define PURE
#define WARN_UNUSED _Check_return_
#define NORETURN __declspec(noreturn)
#define UNUSED
#define CONST_FN
#define LIKELY(x) (x)
#define UNLIKELY(x) (x)
#define HOT
#define COLD
#define ALWAYS_INLINE static __forceinline
#define ALIGN(n) __declspec(align(n))
#define PACKED
#define PRINTF_LIKE(fmt, args)

#else

#define NONNULL(...)
#define PURE
#define WARN_UNUSED
#define NORETURN
#define UNUSED
#define CONST_FN
#define LIKELY(x) (x)
#define UNLIKELY(x) (x)
#define HOT
#define COLD
#define ALWAYS_INLINE inline
#define ALIGN(n)
#define PACKED
#define PRINTF_LIKE(fmt, args)

#endif

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !MACROS_H
