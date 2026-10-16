#include "common.h"

extern s32 scaleRandomToUnsignedHalfwordLimit(s32);
extern void townInitializeObjectEntries(void *, s32, void *);
extern u8 D_800C7604[];
extern u8 D_800D5FC4[];

/* Clear two state values, initialize the actor, and set its handler and randomized counter. */
void townInitializeMotherEventActor(void *actor, void *state, s32 init_param) {
    *(s32 *)((u8 *)state + 0x10) = 0;
    *(s32 *)((u8 *)state + 0xC) = 0;
    townInitializeObjectEntries(actor, init_param, D_800D5FC4);
    *(void **)((u8 *)actor + 0x50) = D_800C7604;
    *(s16 *)((u8 *)actor + 0x6C) = (s16) (scaleRandomToUnsignedHalfwordLimit(0x3F) + 0x15);
}
