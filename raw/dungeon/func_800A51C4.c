#include "common.h"

typedef struct {
    u16 unk0;
    u16 flags;
    u8 pad4[6];
    u16 count;
} DungeonState;

extern DungeonState D_80083460;
extern s16 D_80083228[];
extern s32 func_800AAA10(void *);
extern void func_80047784(void *, s32, s32);

s32 func_800AA924(void *arg0, s32 arg1, void *arg2, u8 *arg3)
{
    DungeonState *state = &D_80083460;

    *(u8 *)((u8 *)arg0 + 0x71) &= 0x7F;
    if (state->flags & 0x2008) {
        *(volatile s8 *)((u8 *)arg0 + 0x9A) = 0xE;
        func_800AAA10(arg2);
        return 1;
    }
    if (*(s32 *)((u8 *)arg0 + 0x1C) & 0x20) {
        register s32 dispatch_id ASM_REG("$2") = 0;
        register s32 state_word ASM_REG("$3") = 0xE;
        register s32 mask ASM_REG("$4");

        *(s8 *)((u8 *)arg0 + 0x9A) = state_word;
        ASM_KEEP(dispatch_id);
        ASM_KEEP(state_word);
        state_word = *(volatile s32 *)((u8 *)arg0 + 0x1C);
        mask = ~0x200;
        state_word &= mask;
        *(s32 *)((u8 *)arg0 + 0x1C) = state_word;
        return func_800AAA10((void *)mask);
    }

    *(s8 *)((u8 *)arg0 + 0x9A) = 0xD;
    *(s8 *)((u8 *)arg0 + 0x9B) = 0;
    *(s32 *)((u8 *)arg0 + 0x8C) = 0;
    if (arg3 != 0) {
        *(u8 **)((u8 *)arg2 + 0x2C) = arg3;
        func_80047784(arg2,
            arg3[((D_80083228[0] + *(s16 *)((u8 *)arg0 + 0x2A) + 0x100) >> 9) & 7],
            0);
    }
    state->count++;
    *(s32 *)((u8 *)arg0 + 0x1C) &= ~0x40000;
    return 1;
}

/* MECHANISM: Natural s0/s1 holds reproduce the 0x20 frame and save contract.
   The second tail ABI pins dispatch $v0=0, RMW $v1, and mask/argument $a0=-0x201.
   A volatile load plus ordinary store lets the RMW store fill the sibcall delay. */
