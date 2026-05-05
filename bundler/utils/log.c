#include "log.h"

#include <stdarg.h>
#include <stdio.h>
#include <vadefs.h>

void logC(const ch* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

void log_autoFlush(const bool flush) {
    setvbuf(stdout, NULL, flush ? _IOLBF : _IONBF , 0);
}

void log_flush(void) {
    fflush(stdout);
}

#define COLORED_LOG(CLR_A, CLR_B)           \
    fprintf(stdout, CLR_A"%s: "CLR_B, tag); \
    va_list args;                           \
    va_start(args, fmt);                    \
    vfprintf(stdout, fmt, args);            \
    va_end(args);                           \
    fputs("\n"LOG_RESET, stdout);           \
    fflush(stdout);

#if LOG_LEVEL >= LOG_LEVEL_INFO
void log_info(const ch* tag, const ch* fmt, ...) {
    COLORED_LOG(LOG_CYAN, LOG_BLUE);
}
#endif

#if LOG_LEVEL >= LOG_LEVEL_WARN
void log_warn(const ch* tag, const ch* fmt, ...) {
    COLORED_LOG(LOG_YELLOW, LOG_BLUE);
}
#endif

#if LOG_LEVEL >= LOG_LEVEL_ERROR
void log_error(const ch* tag, const ch* fmt, ...) {
    COLORED_LOG(LOG_RED, LOG_BLUE);
}
#endif

#if LOG_LEVEL >= LOG_LEVEL_DEBUG
void log_debug(const ch* tag, const ch* fmt, ...) {
    COLORED_LOG(LOG_GREEN, LOG_BLUE);
}
#endif

#undef COLORED_LOG
