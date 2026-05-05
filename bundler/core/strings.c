#include "strings.h"

#include <stdarg.h>
#include <stdio.h>

/* ============================================================
   Internal Helpers
   ============================================================ */

// Thread-local buffer for formatting (256 bytes is usually enough)
static M_threadLocal ch _format_buffer_[1024];

// Forward declaration
static bool _sb_grow(StringB* sb, u32 new_capacity);

/* ============================================================
   String Formatting
   ============================================================ */

str_t str_format(const ch* fmt, ...) {
    if (!fmt) return str_null;
    
    va_list args;
    va_start(args, fmt);
    i32 len = vsnprintf(_format_buffer_, sizeof(_format_buffer_), fmt, args);
    va_end(args);
    
    if (len < 0) return str_null;
    
    u32 ulen = (u32)len;
    ch* copy = (ch*)memClone(_format_buffer_, ulen);
    if (!copy) return str_null;
    
    return str_new(copy, ulen);
}

string_t string_format(const ch* fmt, ...) {
    if (!fmt) return string_null;
    
    va_list args;
    va_start(args, fmt);
    i32 len = vsnprintf(_format_buffer_, sizeof(_format_buffer_), fmt, args);
    va_end(args);
    
    if (len < 0) return string_null;
    
    u32 ulen = (u32)len;
    ch* copy = (ch*)memClone(_format_buffer_, ulen);
    if (!copy) return string_null;
    
    return string_new(copy, ulen);
}

/* ============================================================
   String Builder - Core
   ============================================================ */

static bool _sb_grow(StringB* sb, u32 new_capacity) {
    if (!sb) return false;
    
    u32 new_cap = sb->capacity;
    while (new_cap < new_capacity) {
        new_cap *= 2;
        if (new_cap < sb->capacity) return false; // Overflow
    }
    
    ch* new_data = (ch*)memRealloc(sb->data, new_cap, NULL);
    if (!new_data) return false;
    
    sb->data = new_data;
    sb->capacity = new_cap;
    return true;
}

bool sb_reserve(StringB* sb, u32 needed) {
    if (!sb) return false;
    
    u32 new_len = sb->length + needed;
    if (new_len < sb->length) return false; // Overflow
    
    if (new_len >= sb->capacity) {
        return _sb_grow(sb, new_len + 1); // +1 for null terminator
    }
    
    return true;
}

StringB sb_new(u32 capacity) {
    StringB sb;
    sb_init(&sb, capacity);
    return sb;
}

void sb_init(StringB* sb, u32 capacity) {
    if (!sb) return;
    
    sb->data = (ch*)memAlloc(capacity);
    sb->length = 0;
    sb->capacity = capacity ? capacity : 16;
    
    if (sb->data && sb->capacity > 0) {
        sb->data[0] = '\0';
    }
}

void sb_free(StringB* sb) {
    if (!sb) return;
    
    if (sb->data) {
        memFree(sb->data);
        sb->data = NULL;
    }
    sb->length = 0;
    sb->capacity = 0;
}

void sb_reset(StringB* sb) {
    if (!sb || !sb->data) return;
    sb->length = 0;
    if (sb->capacity > 0) {
        sb->data[0] = '\0';
    }
}

void sb_clear(StringB* sb) {
    if (!sb || !sb->data) return;
    
    memSet(sb->data, 0, sb->length);
    sb->length = 0;
    if (sb->capacity > 0) {
        sb->data[0] = '\0';
    }
}

/* ============================================================
   String Builder - Append
   ============================================================ */

bool sb_append(StringB* sb, str_t str) {
    if (!sb || !str.data) return false;
    if (str.length == 0) return true;
    
    if (!sb_reserve(sb, str.length)) return false;
    
    memCopy(sb->data + sb->length, str.data, str.length);
    sb->length += str.length;
    sb->data[sb->length] = '\0';
    
    return true;
}

bool sb_appendLen(StringB* sb, const ch* buffer, u32 length) {
    if (!sb || !buffer) return false;
    if (length == 0) return true;
    
    if (!sb_reserve(sb, length)) return false;
    
    memCopy(sb->data + sb->length, buffer, length);
    sb->length += length;
    sb->data[sb->length] = '\0';
    
    return true;
}

bool sb_appendCstr(StringB* sb, const ch* string) {
    if (!sb || !string) return false;
    
    u32 len = 0;
    while (string[len]) len++;
    
    return sb_append(sb, str_new(string, len));
}

bool sb_appendChar(StringB* sb, ch c) {
    if (!sb) return false;
    
    if (!sb_reserve(sb, 1)) return false;
    
    sb->data[sb->length++] = c;
    sb->data[sb->length] = '\0';
    
    return true;
}

bool sb_appendFmt(StringB* sb, const ch* fmt, ...) {
    if (!sb || !fmt) return false;
    
    va_list args;
    va_start(args, fmt);
    i32 len = vsnprintf(NULL, 0, fmt, args);
    va_end(args);
    
    if (len < 0) return false;
    
    if (!sb_reserve(sb, (u32)len)) return false;
    
    va_start(args, fmt);
    vsnprintf(sb->data + sb->length, (usize)len + 1, fmt, args);
    va_end(args);
    
    sb->length += (u32)len;
    return true;
}

bool sb_appendRepeat(StringB* sb, str_t str, u32 count) {
    if (!sb || !str.data) return false;
    if (count == 0 || str.length == 0) return true;
    
    u32 total = str.length * count;
    if (total < str.length) return false; // Overflow
    
    if (!sb_reserve(sb, total)) return false;
    
    for (u32 i = 0; i < count; i++) {
        memCopy(sb->data + sb->length + (i * str.length), str.data, str.length);
    }
    
    sb->length += total;
    sb->data[sb->length] = '\0';
    
    return true;
}

/* ============================================================
   String Builder - Prepend
   ============================================================ */

bool sb_prepend(StringB* sb, str_t str) {
    if (!sb || !str.data) return false;
    if (str.length == 0) return true;
    
    if (!sb_reserve(sb, str.length)) return false;
    
    // Shift existing data right
    memMove(sb->data + str.length, sb->data, sb->length);
    
    // Copy new data at beginning
    memCopy(sb->data, str.data, str.length);
    sb->length += str.length;
    sb->data[sb->length] = '\0';
    
    return true;
}

bool sb_prependCstr(StringB* sb, const ch* string) {
    if (!sb || !string) return false;
    
    u32 len = 0;
    while (string[len]) len++;
    
    return sb_prepend(sb, str_new(string, len));
}

bool sb_prependChar(StringB* sb, ch c) {
    if (!sb) return false;
    
    if (!sb_reserve(sb, 1)) return false;
    
    memMove(sb->data + 1, sb->data, sb->length);
    sb->data[0] = c;
    sb->length++;
    sb->data[sb->length] = '\0';
    
    return true;
}

/* ============================================================
   String Builder - Insert/Remove
   ============================================================ */

bool sb_insert(StringB* sb, u32 index, str_t str) {
    if (!sb || !str.data) return false;
    if (index > sb->length) return false;
    if (str.length == 0) return true;
    
    if (!sb_reserve(sb, str.length)) return false;
    
    // Shift data right from insertion point
    memMove(sb->data + index + str.length, 
            sb->data + index, 
            sb->length - index);
    
    // Insert new data
    memCopy(sb->data + index, str.data, str.length);
    sb->length += str.length;
    sb->data[sb->length] = '\0';
    
    return true;
}

bool sb_remove(StringB* sb, u32 index, u32 length) {
    if (!sb) return false;
    if (index >= sb->length) return false;
    
    if (index + length > sb->length) {
        length = sb->length - index;
    }
    
    if (length == 0) return true;
    
    // Shift left
    memMove(sb->data + index, 
            sb->data + index + length, 
            sb->length - (index + length));
    
    sb->length -= length;
    sb->data[sb->length] = '\0';
    
    return true;
}

bool sb_replace(StringB* sb, u32 index, str_t str) {
    if (!sb || !str.data) return false;
    if (index + str.length > sb->length) return false;
    
    memCopy(sb->data + index, str.data, str.length);
    return true;
}

void sb_pop(StringB* sb, u32 amount) {
    if (!sb || amount == 0) return;
    
    if (amount > sb->length) {
        amount = sb->length;
    }
    
    sb->length -= amount;
    sb->data[sb->length] = '\0';
}

void sb_shift(StringB* sb, u32 amount) {
    if (!sb || amount == 0) return;
    
    if (amount > sb->length) {
        amount = sb->length;
    }
    
    u32 new_len = sb->length - amount;
    memMove(sb->data, sb->data + amount, new_len);
    sb->length = new_len;
    sb->data[sb->length] = '\0';
}

/* ============================================================
   String Builder - Transformations
   ============================================================ */

void sb_reverse(StringB* sb) {
    if (!sb || sb->length < 2) return;
    
    u32 half = sb->length / 2;
    for (u32 i = 0; i < half; i++) {
        ch temp = sb->data[i];
        sb->data[i] = sb->data[sb->length - 1 - i];
        sb->data[sb->length - 1 - i] = temp;
    }
}

/* ============================================================
   String Builder - Extraction
   ============================================================ */

str_t sb_substr(const StringB* sb, u32 start, u32 length) {
    if (!sb || start >= sb->length) return str_null;
    
    if (start + length > sb->length) {
        length = sb->length - start;
    }
    
    return str_copy(sb->data + start, length);
}

str_t sb_to_str(const StringB* sb) {
    if (!sb) return str_null;
    return str_copy(sb->data, sb->length);
}

/* ============================================================
   String Comparison
   ============================================================ */

i32 str_cmp(str_t a, str_t b) {
    u32 min_len = a.length < b.length ? a.length : b.length;
    i32 result = memCmp(a.data, b.data, min_len);
    
    if (result != 0) return result;
    if (a.length < b.length) return -1;
    if (a.length > b.length) return 1;
    return 0;
}

bool str_startsWith(str_t str, str_t prefix) {
    if (prefix.length > str.length) return false;
    return memCmp(str.data, prefix.data, prefix.length) == 0;
}

bool str_endsWith(str_t str, str_t suffix) {
    if (suffix.length > str.length) return false;
    return memCmp(str.data + (str.length - suffix.length), 
                  suffix.data, 
                  suffix.length) == 0;
}

u32 str_find(str_t haystack, str_t needle) {
    if (needle.length == 0) return 0;
    if (needle.length > haystack.length) return U32_MAX;
    
    u32 max_idx = haystack.length - needle.length;
    for (u32 i = 0; i <= max_idx; i++) {
        if (memCmp(haystack.data + i, needle.data, needle.length) == 0) {
            return i;
        }
    }
    
    return U32_MAX;
}

u32 str_rfind(str_t haystack, str_t needle) {
    if (needle.length == 0) return haystack.length;
    if (needle.length > haystack.length) return U32_MAX;
    
    u32 i = haystack.length - needle.length;
    while (i > 0) {
        if (memCmp(haystack.data + i, needle.data, needle.length) == 0) {
            return i;
        }
        i--;
    }
    
    // Check index 0
    if (memCmp(haystack.data, needle.data, needle.length) == 0) {
        return 0;
    }
    
    return U32_MAX;
}

/* ============================================================
   String Conversion Helpers
   ============================================================ */

bool str_toI32(str_t str, i32* out) {
    // TODO: Implement proper conversion
    (void)str;
    if (out) *out = 0;
    return false;
}

bool str_toU32(str_t str, u32* out) {
    (void)str;
    if (out) *out = 0;
    return false;
}

bool str_toF64(str_t str, f64* out) {
    (void)str;
    if (out) *out = 0.0;
    return false;
}

str_t str_fromI32(i32 value) {
    ch buf[32];
    i32 len = snprintf(buf, sizeof(buf), "%d", value);
    if (len < 0) return str_null;
    return str_copy(buf, (u32)len);
}

str_t str_fromU32(u32 value) {
    ch buf[32];
    i32 len = snprintf(buf, sizeof(buf), "%u", value);
    if (len < 0) return str_null;
    return str_copy(buf, (u32)len);
}
