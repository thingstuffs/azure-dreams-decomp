#include "common.h"

typedef void (*TownCallback)(void);

extern TownCallback D_800D6B28[3];

/* Invoke the town callback selected by the object state. */
void func_800CBFAC(void *object) {
    volatile TownCallback *callbacks = D_800D6B28;
    s32 state_index = *(s16 *)((s8 *)object + 0x68);
    callbacks[state_index]();
}
