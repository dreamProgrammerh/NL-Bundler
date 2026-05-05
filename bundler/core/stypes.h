#pragma once

#include "platform.h"

typedef void* addr;
typedef unsigned char byte;
typedef char ch;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;

typedef float f32;
typedef double f64;

#if ARCH_is64Bit
    typedef u64 usize;
    typedef i64 isize;
    typedef f64 fsize;
    typedef u64 uptr;
    typedef i64 iptr;

#   define ADDR_SIZE 8
#elif ARCH_is32Bit
    typedef u32 usize;
    typedef i32 isize;
    typedef f32 fsize;
    typedef u32 uptr;
    typedef i32 iptr;

#   define ADDR_SIZE 4
#endif

#define I8_MIN (-128)
#define I16_MIN (-32768)
#define I32_MIN (-2147483647 - 1)
#define I64_MIN (-9223372036854775807LL - 1)

#define I8_MAX 127
#define I16_MAX 32767
#define I32_MAX 2147483647
#define I64_MAX 9223372036854775807LL

#define U8_MIN 0
#define U16_MIN 0
#define U32_MIN 0
#define U64_MIN 0

#define U8_MAX 255
#define U16_MAX 65535
#define U32_MAX 0xffffffffU  /* 4294967295U */
#define U64_MAX 0xffffffffffffffffULL /* 18446744073709551615ULL */

#define F64_NAN (0.0 / 0.0)
#define F64_INF (1.0 / 0.0)
#define F64_NINF (-(1.0 / 0.0))

// Format specifiers for fixed-size types
#define PRIu64 "llu"
#define PRIi64 "lli"
#define PRIu32 "u"
#define PRIi32 "d"
#define PRIu16 "hu"
#define PRIi16 "hd"
#define PRIu8 "hhu"
#define PRIi8 "hhd"

// For usize (changes with architecture)
#if ARCH_is64BIT
#define PRIusize "llu"
#define PRIsize "lli"
#else
#define PRIusize "u"
#define PRIsize "d"
#endif

#include <stdbool.h>