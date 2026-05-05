#pragma once

#include "../core/stypes.h"
#include "../core/typedefs.h"

// ========================================
// File Types
// ========================================

struct FileBuffer {
    ch*     data;
    usize   size;
};

// ========================================
// File Buffer Management
// ========================================

// Read entire file into memory (null-terminated)
void file_read(const ch* path, FileBuffer* fb);

// Deallocate file allocated by file_read
void file_release(FileBuffer* fb);

// ========================================
// File Operations
// ========================================

// Write buffer to file
bool file_write(const ch* path, const void* data, usize size);

// Write string to file
bool file_writeStr(const ch* path, const ch* str);

// Append to file
bool file_append(const ch* path, const void* data, usize size);

// Delete file
bool file_delete(const ch* path);

// Copy file
bool file_copy(const ch* src, const ch* dst);

// Move/rename file
bool file_move(const ch* oldPath, const ch* newPath);

// Get file size
i64 file_size(const ch* path);

// Get last modification time
i64 file_mtime(const ch* path);

// ========================================
// Directory Walking
// ========================================

typedef bool (*FileCallback)(const ch* path, void* userData);

// Walk directory recursively
bool file_walk(const ch* dirPath, FileCallback callback, void* userData);

// Walk directory with filter (extensions like ".c", ".h")
bool file_walkFilter(const ch* dir_path, const ch* const* extensions, 
                    u32 extCount, FileCallback callback, void* userData);