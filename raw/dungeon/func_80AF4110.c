#include "common.h"

typedef struct {
    u8 pad0[0x8C];
    void (*callback)(void *, void *, void *, void *);
} ResourceActor;

extern s32 func_800AB464(ResourceActor *, void *, void *, void *);
extern void func_801717F4();

/* Resume the normal update after the resident action completes. */
void func_80175910(ResourceActor *state, void *motion, void *position, void *actor)
{
    if (func_800AB464(state, motion, position, actor) > 0) {
        state->callback = func_801717F4;
    }
}
