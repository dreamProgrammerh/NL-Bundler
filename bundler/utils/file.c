#include "file.h"
#include "path.h"
#include "log.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#ifdef OS_isWindows
    #include <windows.h>
    #include <sys/stat.h>
    #define F_OK 0
#else
    #include <unistd.h>
    #include <sys/stat.h>
    #include <dirent.h>
    #include <ftw.h>
#endif

// ========================================
// File Buffer
// ========================================

void file_release(FileBuffer* fb) {
    if (!fb) return;
    free(fb->data);
    fb->data = NULL;
    fb->size = 0;
}

// ========================================
// Core File I/O
// ========================================

void file_read(const ch* path, FileBuffer* fb) {
    if (!path) {
        log_error("File", "NULL path provided");
        fb = NULL;
        return;
    }
    
    FILE* f = fopen(path, "rb");
    if (!f) {
        log_error("File", "Cannot open: %s (%s)", path, strerror(errno));
        fb = NULL;
        return;
    }
    
    // Get file size
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    if (size < 0) {
        log_error("File", "Invalid file size: %s", path);
        fclose(f);
        fb = NULL;
        return;
    }
    
    // Allocate buffer (+1 for null terminator)
    fb->data = (ch*)malloc(size + 1);
    if (!fb->data) {
        fclose(f);
        log_error("File", "Out of memory");
        fb = NULL;
        return;
    }
    
    // Read the file
    u64 bytesRead = fread(fb->data, 1, size, f);
    if (bytesRead != (u64)size) {
        log_error("File", "Read error: %s", path);
        fclose(f);
        fb = NULL;
        return;
    }
    
    fb->data[bytesRead] = '\0';  // Null terminate
    fb->size = bytesRead;
    
    fclose(f);
    log_debug("File", "Read %zu bytes from %s", fb->size, path);
}

bool file_write(const ch* path, const void* data, usize size) {
    if (!path || !data) {
        log_error("File", "NULL arguments");
        return false;
    }
    
    FILE* f = fopen(path, "wb");
    if (!f) {
        log_error("File", "Cannot write: %s (%s)", path, strerror(errno));
        return false;
    }
    
    u64 written = fwrite(data, 1, size, f);
    fclose(f);
    
    if (written != size) {
        log_error("File", "Write error: %s", path);
        return false;
    }
    
    log_debug("File", "Wrote %zu bytes to %s", size, path);
    return true;
}

bool file_writeStr(const ch* path, const ch* str) {
    return file_write(path, str, strlen(str));
}

bool file_append(const ch* path, const void* data, usize size) {
    if (!path || !data) return false;
    
    FILE* f = fopen(path, "ab");
    if (!f) return false;
    
    u64 written = fwrite(data, 1, size, f);
    fclose(f);
    
    return written == size;
}

bool file_delete(const ch* path) {
    if (!path) return false;
    return remove(path) == 0;
}

bool file_copy(const ch* src, const ch* dst) {
    FileBuffer fb;
    file_read(src, &fb);
    
    bool result = file_write(dst, fb.data, fb.size);
    file_release(&fb);
    return result;
}

bool file_move(const ch* old_path, const ch* new_path) {
    return rename(old_path, new_path) == 0;
}

i64 file_size(const ch* path) {
    if (!path) return -1;
    
#ifdef OS_isWindows
    struct _stat st;
    if (_stat(path, &st) != 0) return -1;
#else
    struct stat st;
    if (stat(path, &st) != 0) return -1;
#endif
    
    return st.st_size;
}

i64 file_mtime(const ch* path) {
    if (!path) return -1;
    
#ifdef OS_isWindows
    struct _stat st;
    if (_stat(path, &st) != 0) return -1;
    return st.st_mtime;
#else
    struct stat st;
    if (stat(path, &st) != 0) return -1;
    return st.st_mtime;
#endif
}

// ========================================
// Directory Walking
// ========================================

#ifdef OS_isWindows
bool file_walk(const ch* dirPath, FileCallback callback, void* userData) {
    if (!dirPath || !callback) return false;
    
    ch searchPath[PATH_MAX_LEN];
    snprintf(searchPath, sizeof(searchPath), "%s\\*", dirPath);
    
    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA(searchPath, &findData);
    
    if (hFind == INVALID_HANDLE_VALUE) return false;
    
    do {
        if (strcmp(findData.cFileName, ".") == 0 ||
            strcmp(findData.cFileName, "..") == 0) {
            continue;
        }
        
        ch fullPath[PATH_MAX_LEN];
        snprintf(fullPath, sizeof(fullPath), "%s\\%s", dirPath, findData.cFileName);
        
        if (!callback(fullPath, userData)) {
            break;
        }
        
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            file_walk(fullPath, callback, userData);
        }
    } while (FindNextFileA(hFind, &findData));
    
    FindClose(hFind);
    return true;
}
#else
bool file_walk(const ch* dirath, FileCallback callback, void* userData) {
    if (!dirath || !callback) return false;
    
    DIR* dir = opendir(dirath);
    if (!dir) return false;
    
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        ch fullPath[PATH_MAX_LEN];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", dirath, entry->d_name);
        
        if (!callback(fullPath, userData)) {
            break;
        }
        
        // Check if directory (simplified - could use stat for accuracy)
        if (entry->d_type == DT_DIR) {
            file_walk(fullPath, callback, userData);
        }
    }
    
    closedir(dir);
    return true;
}
#endif

// Helper for filter walking
typedef struct WalkFilterData {
    const ch* const* extensions;
    u32 extCount;
    FileCallback userCallback;
    void* userData;
} WalkFilterData;

static bool walk_filterCallback(const ch* path, void* data) {
    WalkFilterData* fd = (WalkFilterData*)data;
    
    // Check if extension matches
    const ch* ext = path_extension(path);
    bool matches = false;
    
    for (u32 i = 0; i < fd->extCount; i++) {
        if (strcmp(ext, fd->extensions[i]) == 0) {
            matches = true;
            break;
        }
    }
    
    if (matches && path_isFile(path)) {
        return fd->userCallback(path, fd->userData);
    }
    
    return true; // Continue walking
}

bool file_walkFilter(const ch* dirath, const ch* const* extensions,
                    u32 extCount, FileCallback callback, void* userData) {
    WalkFilterData fd = {
        .extensions = extensions,
        .extCount = extCount,
        .userCallback = callback,
        .userData = userData
    };
    
    return file_walk(dirath, walk_filterCallback, &fd);
}
