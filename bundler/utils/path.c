#include "path.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef OS_isWindows
    #include <windows.h>
    #include <direct.h>
    #define realpath(N,R) _fullpath(R,N,PATH_MAX_LEN)
    #define mkdir _mkdir
    #define rmdir _rmdir
#else
    #include <unistd.h>
    #include <sys/stat.h>
    #include <limits.h>
    #include <libgen.h>
#endif

ch* path_dirname(ch* path) {
    if (!path || !*path) return (ch*)".";
    
#ifdef OS_isWindows
    // Windows: find last \ or /
    ch* last_sep = NULL;
    for (ch* p = path; *p; p++) {
        if (*p == PATH_SEP || *p == PATH_ALT_SEP) last_sep = p;
    }
    if (!last_sep) return (ch*)".";
    *last_sep = '\0';
    return path;
#else
    return dirname(path);
#endif
}

const ch* path_basename(const ch* path) {
    if (!path || !*path) return ".";
    
    const ch* last_sep = NULL;
    for (const ch* p = path; *p; p++) {
        if (*p == PATH_SEP || *p == PATH_ALT_SEP) last_sep = p;
    }
    
    return last_sep ? last_sep + 1 : path;
}

const ch* path_extension(const ch* path) {
    const ch* base = path_basename(path);
    const ch* dot = strrchr(base, '.');
    return dot ? dot : base + strlen(base);
}

ch* path_join(const ch* a, const ch* b) {
    if (!a || !*a) return strdup(b);
    if (!b || !*b) return strdup(a);
    
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);
    bool need_sep = (a[len_a - 1] != PATH_SEP && a[len_a - 1] != PATH_ALT_SEP);
    
    ch* result = (ch*)malloc(len_a + (need_sep ? 1 : 0) + len_b + 1);
    if (!result) return NULL;
    
    strcpy(result, a);
    if (need_sep) result[len_a] = PATH_SEP;
    strcpy(result + len_a + (need_sep ? 1 : 0), b);
    
    return result;
}

ch* path_normalize(const ch* path) {
    if (!path) return NULL;
    
    // Simple normalization: convert to platform separator
    ch* result = strdup(path);
    if (!result) return NULL;
    
    for (ch* p = result; *p; p++) {
        if (*p == PATH_ALT_SEP) *p = PATH_SEP;
    }
    
    // TODO: Handle . and .. properly (for now just return)
    return result;
}

bool path_isAbsolute(const ch* path) {
    if (!path || !*path) return false;
    
#ifdef OS_isWindows
    // Windows: C:\ or \\server\ ...
    return (strlen(path) >= 2 && path[1] == ':') ||
           (path[0] == PATH_SEP && path[1] == PATH_SEP);
#else
    return path[0] == PATH_SEP;
#endif
}

ch* path_absolute(const ch* path) {
    if (!path) return NULL;
    
    ch resolved[PATH_MAX_LEN];
    if (realpath(path, resolved)) {
        return strdup(resolved);
    }
    return NULL;
}

ch* path_relative(const ch* from, const ch* to) {
    // Simple implementation - full version later... if needed
    if (!from || !to) return NULL;
    
    ch* abs_from = path_absolute(from);
    ch* abs_to = path_absolute(to);
    
    if (!abs_from || !abs_to) {
        free(abs_from);
        free(abs_to);
        return NULL;
    }
    
    // Find common prefix
    const ch* f = abs_from;
    const ch* t = abs_to;
    const ch* last_common = abs_from;
    
    while (*f && *t && *f == *t) {
        if (*f == PATH_SEP) last_common = f;
        f++; t++;
    }
    
    // Count how many dirs up we need to go
    int up_count = 0;
    for (const ch* p = last_common + 1; *p; p++) {
        if (*p == PATH_SEP) up_count++;
    }
    
    // Build relative path
    size_t up_len = up_count * (strlen("..") + 1);
    size_t down_len = strlen(t) + 1;
    ch* result = (ch*)malloc(up_len + down_len);
    
    if (result) {
        ch* w = result;
        for (int i = 0; i < up_count; i++) {
            strcpy(w, "..");
            w += 2;
            *w++ = PATH_SEP;
        }
        strcpy(w, t);
        if (t[0] == PATH_SEP) w++; // Skip leading slash
    }
    
    free(abs_from);
    free(abs_to);
    return result;
}

bool path_exists(const ch* path) {
    if (!path) return false;
    
#ifdef OS_isWindows
    DWORD attrs = GetFileAttributesA(path);
    return attrs != INVALID_FILE_ATTRIBUTES;
#else
    return access(path, F_OK) == 0;
#endif
}

bool path_isDir(const ch* path) {
    if (!path) return false;
    
#ifdef OS_isWindows
    DWORD attrs = GetFileAttributesA(path);
    return (attrs != INVALID_FILE_ATTRIBUTES) && (attrs & FILE_ATTRIBUTE_DIRECTORY);
#else
    struct stat st;
    return stat(path, &st) == 0 && S_ISDIR(st.st_mode);
#endif
}

bool path_isFile(const ch* path) {
    if (!path) return false;
    
#ifdef OS_isWindows
    DWORD attrs = GetFileAttributesA(path);
    return (attrs != INVALID_FILE_ATTRIBUTES) && !(attrs & FILE_ATTRIBUTE_DIRECTORY);
#else
    struct stat st;
    return stat(path, &st) == 0 && S_ISREG(st.st_mode);
#endif
}

ch* path_cwd(void) {
    ch* buf = (ch*)malloc(PATH_MAX_LEN);
    if (!buf) return NULL;
    
#ifdef OS_isWindows
    if (!_getcwd(buf, PATH_MAX_LEN)) {
        free(buf);
        return NULL;
    }
#else
    if (!getcwd(buf, PATH_MAX_LEN)) {
        free(buf);
        return NULL;
    }
#endif
    return buf;
}

bool path_chdir(const ch* path) {
    if (!path) return false;
    
#ifdef OS_isWindows
    return _chdir(path) == 0;
#else
    return chdir(path) == 0;
#endif
}

bool path_mkdir(const ch* path, bool recursive) {
    if (!path) return false;
    if (path_exists(path)) return true;
    
#ifdef OS_isWindows
    if (recursive) {
        ch* parent = strdup(path);
        if (!parent) return false;
        ch* dir = path_dirname(parent);
        if (dir && strlen(dir) > 1) { // Don't try to create "."
            path_mkdir(dir, true);
        }
        free(parent);
    }
    return mkdir(path) == 0;
#else
    if (recursive) {
        ch* parent = strdup(path);
        if (!parent) return false;
        ch* dir = path_dirname(parent);
        if (dir && strcmp(dir, ".") != 0 && strcmp(dir, "/") != 0) {
            path_mkdir(dir, true);
        }
        free(parent);
    }
    return mkdir(path, 0755) == 0;
#endif
}

bool path_rmdir(const ch* path) {
    if (!path) return false;
    return rmdir(path) == 0;
}