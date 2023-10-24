#pragma once

#include <stdio.h>
#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

// Disable debug and trace logging for release builds.
#if RELEASE == 1
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif

typedef struct loggerState {
    char* logQueue;
    int fileLogQueueCnt;
    FILE* fileHandle;
} loggerState;

typedef enum logLevel {
    LOG_LEVEL_FATAL = 0,
    LOG_LEVEL_ERROR = 1,
    LOG_LEVEL_WARN = 2,
    LOG_LEVEL_INFO = 3,
    LOG_LEVEL_DEBUG = 4,
    LOG_LEVEL_TRACE = 5
} logLevel;

char loggerInit(int* memoryRequirement, const char* logFile, void* state);
void loggerShutdown();

void logToFile(logLevel level, char logToConsole, const char* message, ...);

void logOutput(logLevel level, const char* message, ...);

// Logs a fatal-level message.
#define FATAL(message, ...) logOutput(LOG_LEVEL_FATAL, message, ##__VA_ARGS__);
#define FFATAL(message, toConsole, ...) logToFile(LOG_LEVEL_FATAL, toConsole, message, ##__VA_ARGS__);

#ifndef ERROR
// Logs an error-level message.
#define ERROR(message, ...) logOutput(LOG_LEVEL_ERROR, message, ##__VA_ARGS__);
#define FERROR(message, toConsole, ...) logToFile(LOG_LEVEL_ERROR, toConsole, message, ##__VA_ARGS__);
#endif

#if LOG_WARN_ENABLED == 1
// Logs a warning-level message.
#define WARN(message, ...) logOutput(LOG_LEVEL_WARN, message, ##__VA_ARGS__);
#define FWARN(message, toConsole, ...) logToFile(LOG_LEVEL_WARN, toConsole, message, ##__VA_ARGS__);
#else
// Does nothing when LOG_WARN_ENABLED is false
#define WARN(message, ...)
#define FWARN(message, toConsole, ...)
#endif

#if LOG_INFO_ENABLED == 1
// Logs a info-level message.
#define INFO(message, ...) logOutput(LOG_LEVEL_INFO, message, ##__VA_ARGS__);
#define FINFO(message, toConsole, ...) logToFile(LOG_LEVEL_INFO, toConsole, message, ##__VA_ARGS__);
#else
// Does nothing when LOG_INFO_ENABLED is false
#define INFO(message, ...)
#define FINFO(message, toConsole, ...)
#endif

#if LOG_DEBUG_ENABLED == 1
// Logs a debug-level message.
#define DEBUG(message, ...) logOutput(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);
#define FDEBUG(message, toConsole, ...) logToFile(LOG_LEVEL_DEBUG, toConsole, message, ##__VA_ARGS__);
#else
// Does nothing when LOG_DEBUG_ENABLED is false
#define DEBUG(message, ...)
#define FDEBUG(message, toConsole, ...)
#endif

#if LOG_TRACE_ENABLED == 1
// Logs a trace-level message.
#define TRACE(message, ...) logOutput(LOG_LEVEL_TRACE, message, ##__VA_ARGS__);
#define FTRACE(message, toConsole, ...) logToFile(LOG_LEVEL_TRACE, toConsole, message, ##__VA_ARGS__);
#else
// Does nothing when LOG_TRACE_ENABLED is false
#define TRACE(message, ...)
#define FTRACE(message, toConsole, ...)
#endif
