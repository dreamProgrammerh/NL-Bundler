/// This header will contain every struct/union typedef,
///  to avoid circular referencing by adding forward declaration
#pragma once

#include "stypes.h"

typedef union cast32 {
    u32 u;
    i32 i;
    f32 f;
} cast32;

typedef union cast64 {
    u64 u;
    i64 i;
    f64 f;
} cast64;

// memory.h
typedef struct mem_t mem_t;

// string.h
typedef struct str_t str_t;
typedef struct string_t string_t;
typedef struct StringB StringB;
typedef struct PackedStrings PackedStrings;

// file.h
typedef struct FileBuffer FileBuffer;