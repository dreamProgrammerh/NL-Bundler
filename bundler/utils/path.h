#pragma once

#include "../core/stypes.h"

// ========================================
// Path Operations
// ========================================

// Get parent directory (modifies string, returns pointer to the '/')
ch* path_dirname(ch* path);

// Get basename (last component)
const ch* path_basename(const ch* path);

// Get extension (including dot, e.g. ".c")
const ch* path_extension(const ch* path);

// Join two paths (allocates new string)
ch* path_join(const ch* a, const ch* b);

// Normalize path (remove . and .., handle multiple slashes)
ch* path_normalize(const ch* path);

// Check if path is absolute
bool path_isAbsolute(const ch* path);

// Get absolute path (realpath wrapper)
ch* path_absolute(const ch* path);

// Get relative path from 'from' to 'to'
ch* path_relative(const ch* from, const ch* to);

// Check if path exists
bool path_exists(const ch* path);

// Check if path is a directory
bool path_isDir(const ch* path);

// Check if path is a file
bool path_isFile(const ch* path);

// Get current working directory
ch* path_cwd(void);

// Change directory
bool path_chdir(const ch* path);

// Create directory (recursive option)
bool path_mkdir(const ch* path, bool recursive);

// Remove directory (empty)
bool path_rmdir(const ch* path);

// ========================================
// Path Constants
// ========================================

#if OS_isWindows
    #define PATH_SEP '\\'
    #define PATH_SEP_STR "\\"
    #define PATH_ALT_SEP '/'
#else
    #define PATH_SEP '/'
    #define PATH_SEP_STR "/"
    #define PATH_ALT_SEP '/'
#endif

#define PATH_MAX_LEN 4096