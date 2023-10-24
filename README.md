# File Logger

Must initialize before use.

Similar to how Vulkan initializes systems.

First call gives back the needed memory requirement. State parameter must be zero.

```c
int memoryRequirement;
loggerInit(&memoryRequirement, "Doesn't matter", 0);
```
Make sure to reference the memoryRequirement parameter. loggerFile isn't used in this stage. state MUST be zero.

Then malloc the needed memory.

```c
void* loggerMemState;
loggerMemState = malloc(sizeof(memoryRequirement));
```

Then finally actually initalize the logger system.

```c
loggerInit(&memoryRequirement, "appLogger.log", loggerMemState);
```

The loggerFile does matter in this call.

Parameters `memoryRequirement` and `loggerMemState` should not be local to a function.

Do NOT do this setup more than once. Behavior is undefined. Could leak memory or corrupt files.

Call `loggerShutdown()` after all logging.

## Logger functions

Console log functions E.x `ERROR("Message is %s.\n", "put here")`

- FATAL
- ERROR
- INFO
- DEBUG
- TRACE

File log functions. Additional parameter `char logToConsoleAswell`. E.x `FERROR("Message is %s.\n", 0, "put here")`

- FFATAL
- FERROR
- FINFO
- FDEBUG
- FTRACE

## Example Project Setup/Shutdown

```c
typedef struct state{
    int memoryRequirement;
    void* loggerMemState;
} state;

int main(){
    state* state = malloc(sizeof(struct state));

    loggerInit(&state->memoryRequirement, "appLogger.log", 0);
    state->loggerMemState = malloc(state->memoryRequirement);
    loggerInit(&state->memoryRequirement, "appLogger.log", state->loggerMemState);
    //Can now use logger functions

    FERROR("Hello %d", 1, 23);

    loggerShutdown();
}
```

## Limitations

- Can only use one logger file per setup.

