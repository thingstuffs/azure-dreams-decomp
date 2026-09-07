#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern void *func_8003FD64();
extern void func_8004491C();
extern s32 rand();

extern u8 D_800D5AC0[];
extern u8 D_800D5CA0[];
extern s16 D_800E2468[];

void func_800D5DCC(void *arg0, s16 arg1, s32 arg2)
{
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a1;
    void *temp_a2;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_v0;

    temp_v0 = func_8003FD64(0x211, arg0);
    if (temp_v0 != NULL) {
        FIELD(temp_v0, void *, 0x10) = D_800D5CA0;
        FIELD(FIELD(temp_v0, void *, 8), u16, 2) =
            FIELD(FIELD(arg0, void *, 8), u16, 2);
        FIELD(FIELD(temp_v0, void *, 8), u16, 6) =
            FIELD(FIELD(arg0, void *, 8), u16, 6);
        FIELD(FIELD(temp_v0, void *, 8), s16, 0xA) =
            FIELD(FIELD(arg0, void *, 8), u16, 0xA) - 0x14;
        temp_s0 = ((arg1 >> 7) & 0x1C) + (u8 *)D_800E2468;
        temp_a0 = FIELD(temp_v0, void *, 8);
        FIELD(temp_a0, u16, 2) += FIELD(temp_s0, s16, 0) * 0x10;
        temp_a0_2 = FIELD(temp_v0, void *, 8);
        FIELD(temp_a0_2, u16, 6) += FIELD(temp_s0, s16, 2) * 0x10;
        FIELD(FIELD(temp_v0, void *, 0xC), s16, 6) = 6;
        FIELD(FIELD(temp_v0, void *, 8), s32, 0xC) =
            ((rand(temp_a0_2) & 0x7FFF) - 0x4000) << 6;
        FIELD(FIELD(temp_v0, void *, 8), s32, 0x10) =
            ((rand() & 0x7FFF) - 0x4000) << 6;
        FIELD(FIELD(temp_v0, void *, 8), s32, 0x14) =
            ((rand() & 0x7FFF) - 0x4000) << 5;
        temp_a1 = FIELD(temp_v0, void *, 8);
        FIELD(temp_a1, s32, 0xC) += FIELD(temp_s0, s16, 0) * 0x160000;
        temp_s0_2 = (u8 *)temp_v0 + 0x20;
        temp_a2 = FIELD(temp_v0, void *, 8);
        FIELD(temp_a2, s32, 0x10) += FIELD(temp_s0, s16, 2) * 0x160000;
        FIELD(temp_s0_2, u16, 0x14) = arg1;
        FIELD(temp_s0_2, s16, 0x32) = 7;
        FIELD(temp_s0_2, s16, 0x34) = 7;
        func_8004491C(temp_v0, D_800D5AC0, temp_a2);
        FIELD(temp_v0, s32, 0x20) = arg2;
        FIELD(temp_s0_2, s32, 8) = arg2;
    }
}
