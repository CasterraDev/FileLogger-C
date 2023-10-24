#include "logger.h"
#include <stdint.h>
#include <stdlib.h>

typedef struct state{
    int memoryRequirement;
    void* loggerMemState;
} state;

int main(){
    state* state = malloc(sizeof(struct state));
    loggerInit(&state->memoryRequirement, "appLogger.log", 0);
    state->loggerMemState = malloc(state->memoryRequirement);
    loggerInit(&state->memoryRequirement, "appLogger.log", state->loggerMemState);
    FERROR("Hello %d", 1, 23);
    loggerShutdown();
}
