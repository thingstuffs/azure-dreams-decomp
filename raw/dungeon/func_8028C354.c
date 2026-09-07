#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type, offset) (*(type *)((s8 *)(expr) + (offset)))

extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 D_80044BB0[3];
extern s32 D_800A5AF0[3];

void func_8001F354(s16 arg0, s16 arg1, s32 arg2, s32 arg3)
{
    register s16 final_arg0 ASM_REG("$20");
    register s32 held_arg3 ASM_REG("$21");
    u16 flags;
    void *temp_a0;
    void *temp_v0;
    s16 *temp_v1;
    s16 *temp_v1_2;

    held_arg3 = arg3;
    ASM_KEEP_NV(held_arg3);
    temp_v0 = func_8003FC64(2);
    if (temp_v0 != NULL) {
        final_arg0 = arg0;
        ASM_KEEP(final_arg0);
        FIELD(temp_v0, s32 *, 0x10) = (s32)D_800A5AF0;
        func_8004491C(temp_v0, D_80044BB0);
        temp_v1 = (s16 *)FIELD(temp_v0, void *, 8);
        temp_v1[1] = arg0 + 0x280;
        temp_v1[3] = arg1;
        temp_v1[5] = 1;
        temp_a0 = FIELD(temp_v0, void *, 0xC);
        FIELD(temp_a0, s16, 0x1C) = 0x2000;
        FIELD(temp_a0, s16, 0x1E) = 0x1000;
        FIELD(temp_a0, s32, 8) = held_arg3;
        if ((arg2 << 0x10) != 0) {
            FIELD(temp_a0, s32, 0xC) = 0x202080;
        } else {
            FIELD(temp_a0, s32, 0xC) = 0x808080;
        }
        flags = FIELD(temp_a0, u16, 0x14);
        FIELD(temp_a0, s16, 0x10) = 0x20;
        temp_v1_2 = (s16 *)(temp_v0 + 0x20);
        FIELD(temp_a0, u16, 0x14) = flags | 0xC;
        temp_v1_2[3] = 0x18;
        temp_v1_2[4] = final_arg0;
    }
}
