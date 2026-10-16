#include "common.h"

typedef struct {
    u8 pad0[0x8C];
    void (*callback)(void *, void *, void *, void *);
} ResourceActor;

extern s32 func_800AC7EC(ResourceActor *, void *, void *, void *);
extern void func_8017140C();

/* Resume the normal update after the resident action completes. */
void func_80175834(ResourceActor *state, void *motion, void *position, void *actor)
{
    if (func_800AC7EC(state, motion, position, actor) > 0) {
        state->callback = func_8017140C;
    }
}
