#include "common.h"

extern s32 func_800374F4(s32);
extern void func_800C2E84(void *, s32, void *);
extern u8 D_800C7604[];
extern u8 D_800D5FC4[];

/* Clear two state values, initialize the actor, and set its handler and randomized counter. */
void func_800C7A6C(void *actor, void *state, s32 init_param) {
    *(s32 *)((u8 *)state + 0x10) = 0;
    *(s32 *)((u8 *)state + 0xC) = 0;
    func_800C2E84(actor, init_param, D_800D5FC4);
    *(void **)((u8 *)actor + 0x50) = D_800C7604;
    *(s16 *)((u8 *)actor + 0x6C) = (s16) (func_800374F4(0x3F) + 0x15);
}
