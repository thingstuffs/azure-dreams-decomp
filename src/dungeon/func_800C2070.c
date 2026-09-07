#include "common.h"

extern s16 D_80083780[];
extern u8 D_800C75D0[];
extern s8 D_800E3D20[];
extern void func_800C7898(void);

s32 func_800C77D0(s32 arg0, void *arg1, s32 arg2, s16 arg3) {
    s32 d;
    s32 rhs;
    s32 result;
    void *old;
    u8 *state;
    u8 *slot;
    s32 arg2keep;

    d = D_80083780[1];
    rhs = *(s16 *)((u8 *)arg1 + 2);
    d -= rhs;
    if (d < 0) d = -d;
    if (d >= 0xC1) {
        func_800C7898();
        return 0;
    }
    arg2keep = arg2;
    ASM_KEEP(arg2keep);   /* MATCH pin: load-bearing for the whole function shape */
    d = D_80083780[3];
    rhs = *(s16 *)((u8 *)arg1 + 6);
    d -= rhs;
    if (d < 0) d = -d;
    if (d >= 0xC1) {
        func_800C7898();
        return 0;
    }

    state = (u8 *)&D_80083178;
    slot = state + 0xB8;
    old = *(void **)(slot + 0xC);
    *(s32 *)(slot + 0x34) = arg0;
    *(void **)(slot + 0xC) = arg1;
    *(s32 *)(slot + 0x28) = 0;
    *(void **)slot = slot + 4;
    result = old != arg1;
    if (*(s32 *)(slot + 0x14) != 9) result |= 2;
    *(s32 *)(slot + 0x14) = 9;
    *(s32 *)(slot + 0x18) = 0;
    *(s16 *)(slot + 0x26) = arg3;
    *(void **)(state + 0xB4) = D_800C75D0;
    if (result & 1) D_800E3D20[0] = arg2keep;
    *(s16 *)(slot + 0x24) = arg2;
    return result;
}

/* MECHANISM: A guarded $v0 distance accumulator plus separate rhs halfword gives
   the retail load/subtract roles; the post-merge keeps preserve its abs CFG.
   The late $t2 arg copy fills the threshold delay, while void-call/return-zero
   exposes the frameless SHAPE-C dispatcher tail and its zero return delay. */
