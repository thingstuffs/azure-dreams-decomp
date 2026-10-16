#include "common.h"

typedef struct {
    u8 pad0[0x8C];
    void (*callback)(void *, void *, void *, void *);
} ResourceActor;

extern s32 func_800AC480(ResourceActor *, void *, void *, void *);
extern void func_801713A8();

/* Resume the update callback once the resident state check succeeds. */
void func_8017437C(ResourceActor *state, void *motion, void *position, void *actor)
{
    if (func_800AC480(state, motion, position, actor)) {
        state->callback = func_801713A8;
    }
}
