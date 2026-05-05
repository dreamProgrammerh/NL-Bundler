#pragma once
#include "../core/stypes.h"

#define LOG_LEVEL_INFO  0
#define LOG_LEVEL_WARN  1
#define LOG_LEVEL_ERROR 2
#define LOG_LEVEL_DEBUG 3

#ifndef LOG_LEVEL
#   define LOG_LEVEL LOG_LEVEL_INFO
#endif

void log_autoFlush(bool flush);
void log_flush(void);
void logC(const ch* fmt, ...);

#if LOG_LEVEL >= LOG_LEVEL_INFO
    void log_info(const ch* tag, const ch* fmt, ...);
#else
#   define log_info(tag, fmt, ...) // log_info(tag, fmt, __VA_ARGS__)
#endif

#if LOG_LEVEL >= LOG_LEVEL_WARN
    void log_war(const ch* tag, const ch* fmt, ...);
#else
#   define log_war(tag, fmt, ...) // log_war(tag, fmt, __VA_ARGS__)
#endif

#if LOG_LEVEL >= LOG_LEVEL_ERROR
    void log_error(const ch* tag, const ch* fmt, ...);
#else
#   define log_error(tag, fmt, ...) // log_error(tag, fmt, __VA_ARGS__)
#endif

#if LOG_LEVEL >= LOG_LEVEL_DEBUG
    void log_debug(const ch* tag, const ch* fmt, ...);
#else
#   define log_debug(tag, fmt, ...) // log_debug(tag, fmt, __VA_ARGS__)
#endif

// Colors
#define LOG_RESET   "\x1b[0m"
#define LOG_RED     "\x1b[31m"
#define LOG_GREEN   "\x1b[32m"
#define LOG_YELLOW  "\x1b[33m"
#define LOG_BLUE    "\x1b[34m"
#define LOG_MAGENTA "\x1b[35m"
#define LOG_CYAN    "\x1b[36m"