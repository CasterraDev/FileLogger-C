#include "logger.h"
#include <stdint.h>
#include <stdlib.h>

int main(){
    void* log;
    int mem;
    loggerInit(&mem, "appLogger.log", 0);
    log = malloc(mem);
    loggerInit(&mem, "appLogger.log", log);
    FERROR("Hello %d", 1, 23);
    loggerShutdown();
}
