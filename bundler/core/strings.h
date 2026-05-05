#pragma once

#include "typedefs.h"
#include "memory.h"

/* ============================================================
   String Types
   ============================================================ */

/**
 * Immutable string view - does NOT own memory.
 * Use for string literals and temporary views.
 */
struct str_t {
    const ch* data;
    u32 length;
};

/**
 * Mutable owned string - owns memory, can be modified.
 * Use when you need to modify or extend strings.
 */
struct string_t {
    ch* data;
    u32 length;
};

/**
 * Dynamic string builder - grows automatically.
 * Use for building strings incrementally.
 */
struct StringB {
    ch* data;
    u32 length;
    u32 capacity;
};

/**
 * Packed string storage - stores multiple strings in single allocation.
 * TODO: Complete implementation
 */
struct PackedStrings {
    u32* references;  // Offsets into data pool + 1 and pool comes after
    u32 count;
    u32 capacity;
};

/* ============================================================
   Constants
   ============================================================ */

#define str_null ((str_t){ .data = NULL, .length = 0 })
#define string_null ((string_t){ .data = NULL, .length = 0 })

#define str_lit(s) str_new((s), sizeof(s) - 1)
#define string_lit(s) string_new((s), sizeof(s) - 1)

/* ============================================================
   Constructors
   ============================================================ */

/**
 * Create string view from existing data (no copy).
 */
inline
str_t str_new(const ch* data, u32 length) {
    str_t s;
    s.data = data;
    s.length = length;
    return s;
}

/**
 * Create mutable string from existing buffer (no copy).
 */
inline
string_t string_new(ch* data, u32 length) {
    string_t s;
    s.data = data;
    s.length = length;
    return s;
}

/**
 * Create copy of data as immutable string (allocates memory).
 */
inline
str_t str_copy(const ch* data, u32 length) {
    ch* copy = (ch*)memClone(data, length);
    return str_new(copy, length);
}

/**
 * Create copy of data as mutable string (allocates memory).
 */
inline
string_t string_copy(const ch* data, u32 length) {
    ch* copy = (ch*)memClone(data, length);
    return string_new(copy, length);
}

/**
 * Format string using printf-style format (allocates memory).
 * 
 * @param fmt  Format string (not data buffer!)
 * @param ...  Format arguments
 * 
 * Example: str_t s = str_format("Hello %s", "World");
 */
str_t str_format(const ch* fmt, ...);

/**
 * Format string using printf-style format (allocates mutable memory).
 */
string_t string_format(const ch* fmt, ...);

/* ============================================================
   String Builder (StringB)
   ============================================================ */

/**
 * Create new string builder with initial capacity.
 * 
 * @param capacity Initial capacity in bytes
 * @return New string builder (caller must free with sb_free)
 */
StringB sb_new(u32 capacity);

/**
 * Initialize existing string builder.
 * 
 * @param sb       Pointer to builder
 * @param capacity Initial capacity
 */
void sb_init(StringB* sb, u32 capacity);

/**
 * Free string builder memory.
 * 
 * @param sb Builder to free (can be NULL)
 */
void sb_free(StringB* sb);

/**
 * Reset builder to empty (does not free memory).
 * 
 * @param sb Builder to reset
 */
void sb_reset(StringB* sb);

/**
 * Clear builder contents (zero out memory).
 * 
 * @param sb Builder to clear
 */
void sb_clear(StringB* sb);

/**
 * Ensure builder has at least 'needed' bytes available.
 * 
 * @param sb     Builder
 * @param needed Additional bytes needed
 * @return true if successful, false on allocation failure
 */
bool sb_reserve(StringB* sb, u32 needed);

/* ============================================================
   String Builder - Append Operations
   ============================================================ */

/**
 * Append string view to builder.
 * 
 * @param sb   Builder
 * @param str  String view to append
 * @return true on success, false on allocation failure
 */
bool sb_append(StringB* sb, str_t str);

/**
 * Append length bytes to builder.
 * 
 * @param sb   Builder
 * @param buffer Bytes buffer
 * @param length Number of bytes to append from the buffer
 * @return true on success, false on allocation failure
 */
bool sb_appendLen(StringB* sb, const ch* buffer, const u32 length);

/**
 * Append C string to builder.
 * 
 * @param sb     Builder
 * @param string Null-terminated C string
 * @return true on success, false on allocation failure
 */
bool sb_appendCstr(StringB* sb, const ch* string);

/**
 * Append character to builder.
 * 
 * @param sb Builder
 * @param ch Character to append
 * @return true on success, false on allocation failure
 */
bool sb_appendChar(StringB* sb, ch c);

/**
 * Append formatted string to builder.
 * 
 * @param sb  Builder
 * @param fmt Format string
 * @param ... Format arguments
 * @return true on success, false on allocation failure
 */
bool sb_appendFmt(StringB* sb, const ch* fmt, ...);

/**
 * Append string multiple times.
 * 
 * @param sb     Builder
 * @param str    String to repeat
 * @param count  Number of times to repeat
 * @return true on success, false on allocation failure
 */
bool sb_appendRepeat(StringB* sb, str_t str, u32 count);

/* ============================================================
   String Builder - Prepend Operations
   ============================================================ */

/**
 * Prepend string view to builder.
 * 
 * @param sb   Builder
 * @param str  String view to prepend
 * @return true on success, false on allocation failure
 */
bool sb_prepend(StringB* sb, str_t str);

/**
 * Prepend C string to builder.
 * 
 * @param sb     Builder
 * @param string Null-terminated C string
 * @return true on success, false on allocation failure
 */
bool sb_prependCstr(StringB* sb, const ch* string);

/**
 * Prepend character to builder.
 * 
 * @param sb Builder
 * @param ch Character to prepend
 * @return true on success, false on allocation failure
 */
bool sb_prependChar(StringB* sb, ch c);

/* ============================================================
   String Builder - Insert/Remove Operations
   ============================================================ */

/**
 * Insert string at index.
 * 
 * @param sb    Builder
 * @param index Position to insert (0 = beginning)
 * @param str   String to insert
 * @return true on success, false on failure (invalid index or allocation)
 */
bool sb_insert(StringB* sb, u32 index, str_t str);

/**
 * Remove substring.
 * 
 * @param sb     Builder
 * @param index  Start index
 * @param length Number of characters to remove
 * @return true on success, false on invalid parameters
 */
bool sb_remove(StringB* sb, u32 index, u32 length);

/**
 * Replace substring at index.
 * 
 * @param sb    Builder
 * @param index Start index
 * @param str   Replacement string
 * @return true on success, false on invalid index
 */
bool sb_replace(StringB* sb, u32 index, str_t str);

/**
 * Remove from end (pop).
 * 
 * @param sb     Builder
 * @param amount Number of characters to remove from end
 */
void sb_pop(StringB* sb, u32 amount);

/**
 * Remove from beginning (shift).
 * 
 * @param sb     Builder
 * @param amount Number of characters to remove from start
 */
void sb_shift(StringB* sb, u32 amount);

/* ============================================================
   String Builder - Transformations
   ============================================================ */

/**
 * Reverse the string in place.
 * 
 * @param sb Builder
 */
void sb_reverse(StringB* sb);

/* ============================================================
   String Builder - Extraction
   ============================================================ */

/**
 * Extract substring as new immutable string.
 * 
 * @param sb     Builder
 * @param start  Start index
 * @param length Number of characters
 * @return New string view (allocates memory)
 */
str_t sb_substr(const StringB* sb, u32 start, u32 length);

/**
 * Convert builder to immutable string view.
 * 
 * @param sb Builder
 * @return String view (allocates memory)
 */
str_t sb_toStr(const StringB* sb);

/**
 * Get C string pointer (null-terminated).
 * Note: Modifying builder invalidates this pointer.
 * 
 * @param sb Builder
 * @return Null-terminated C string
 */
inline
const ch* sb_cstr(const StringB* sb) {
    return sb->data;
}

/**
 * Get current length.
 */
inline
u32 sb_length(const StringB* sb) {
    return sb->length;
}

/**
 * Check if builder is empty.
 */
inline
bool sb_empty(const StringB* sb) {
    return sb->length == 0;
}

/* ============================================================
   String Comparison
   ============================================================ */

/**
 * Compare two string views.
 * 
 * @param a First string
 * @param b Second string
 * @return <0 if a<b, 0 if equal, >0 if a>b
 */
i32 str_cmp(str_t a, str_t b);

/**
 * Check if string views are equal.
 */
inline
bool str_eq(str_t a, str_t b) {
    return a.length == b.length && str_cmp(a, b) == 0;
}

/**
 * Check if string starts with prefix.
 */
bool str_startsWith(str_t str, str_t prefix);

/**
 * Check if string ends with suffix.
 */
bool str_endsWith(str_t str, str_t suffix);

/**
 * Find first occurrence of substring.
 * 
 * @param haystack String to search in
 * @param needle   Substring to find
 * @return Index of first occurrence, or U32_MAX if not found
 */
u32 str_find(str_t haystack, str_t needle);

/**
 * Find last occurrence of substring.
 * 
 * @param haystack String to search in
 * @param needle   Substring to find
 * @return Index of last occurrence, or U32_MAX if not found
 */
u32 str_rfind(str_t haystack, str_t needle);

/* ============================================================
   String Conversion
   ============================================================ */

/**
 * Convert string to integer.
 * 
 * @param str String to convert
 * @param out Output integer (set even on partial conversion)
 * @return true if conversion succeeded, false on error
 */
bool str_toI32(str_t str, i32* out);
bool str_toU32(str_t str, u32* out);
bool str_toF64(str_t str, f64* out);

/**
 * Convert integer to string (allocates).
 */
str_t str_fromI32(i32 value);
str_t str_fromU32(u32 value);