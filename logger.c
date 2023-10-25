#include "logger.h"

// TODO: temporary
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

static loggerState* systemPtr;

void sendTextToFile(const char* m) {
    int l = strlen(m);
    int written = 0;
    fwrite(m, l, 1, systemPtr->fileHandle);
}

char loggerInit(int* memoryRequirement, const char* logFile, void* state) {
    *memoryRequirement = sizeof(loggerState);
    if (state == 0) {
        return 1;
    }
    systemPtr = state;

    systemPtr->fileHandle = fopen(logFile, "w");

    if (!systemPtr->fileHandle) {
        printf("Error opening logger file.");
        return 0;
    }
    return 1;
}

void loggerShutdown() {
    fflush(systemPtr->fileHandle);
    fclose(systemPtr->fileHandle);
    systemPtr = 0;
}

void logOutput(logLevel level, char logToConsole, char logToFile, const char* message, ...) {
    const char* levelStr[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]:  ",
                               "[INFO]:  ", "[DEBUG]: ", "[TRACE]: "};
    char isError = level < 2;

    // Technically imposes a 32k character limit on a single log entry, but...
    // DON'T DO THAT!
    char outMessage[32000];
    memset(outMessage, 0, sizeof(outMessage));

    // Format original message.
    __builtin_va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(outMessage, 32000, message, arg_ptr);
    va_end(arg_ptr);

    char finalMessage[32000];
    sprintf(finalMessage, "%s%s\n", levelStr[level], outMessage);

    if (logToConsole) {
        if (isError) {
            printf("%s\n", finalMessage);
        } else {
            printf("%s\n", finalMessage);
        }
    }
    
    if (logToFile){
        sendTextToFile(finalMessage);
    }
}

void reportAssertFailure(const char* expression, const char* message,
                         const char* file, int line) {
    logOutput(LOG_LEVEL_FATAL,1,1,
              "Assertion Failure: %s, message: '%s', in file: %s, line: %d\n",
              expression, message, file, line);
}
