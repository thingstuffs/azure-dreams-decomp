#include "common.h"

typedef struct {
    u8 pad0[0x8C];
    void (*callback)(void *, void *, void *, void *);
} ResourceActor;

extern s32 func_800ABDBC(ResourceActor *, void *, void *, void *);
extern void func_80170E54();

/* Resume the update callback once the resident state check succeeds. */
void func_801736BC(ResourceActor *state, void *motion, void *position, void *actor)
{
    if (func_800ABDBC(state, motion, position, actor)) {
        state->callback = func_80170E54;
    }
}
