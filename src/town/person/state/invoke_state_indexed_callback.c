#include "common.h"

typedef void (*TownCallback)(void *, s32, void *);

extern TownCallback D_800D6B28[];

/* Invoke the town callback selected by the object state. */
void invoke_state_indexed_callback(void *object, s32 context, void *motion) {
    TownCallback *callbacks = D_800D6B28;
    s32 state_index = *(s16 *)((s8 *)object + 0x68);
    callbacks[state_index](object, context, motion);
}
