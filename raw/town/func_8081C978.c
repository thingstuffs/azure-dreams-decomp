#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern void *func_8003FC64();
extern void func_8004491C();
extern s32 rand();
extern u8 D_80026B00[];
extern u8 D_80045340[];
extern u8 D_800F7944[];

void func_80026978(void *arg0)
{
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_v0_2;
    s32 color;
    void *temp_s0;
    void *temp_s2;
    void *temp_v1;
    void *temp_v0;

    temp_v0 = func_8003FC64(0x136);
    if (temp_v0 != NULL) {
        FIELD(temp_v0, void *, 0x10) = D_80026B00;
        func_8004491C(temp_v0, D_80045340);
        temp_s2 = FIELD(temp_v0, void *, 8);
        temp_s0 = FIELD(temp_v0, void *, 0xC);
        temp_a0 = (FIELD(arg0, u16, 2) + (rand() % 40)) - 0x14;
        FIELD(temp_s2, s16, 2) = temp_a0;
        temp_a0_2 = (FIELD(arg0, u16, 6) + (rand(temp_a0) % 40)) - 0x14;
        FIELD(temp_s2, s16, 6) = temp_a0_2;
        temp_a0_3 = (FIELD(arg0, u16, 0xA) + (rand(temp_a0_2) % 40)) - 0x14;
        FIELD(temp_s2, s16, 0xA) = temp_a0_3;
        FIELD(temp_s2, s32, 0xC) = FIELD(arg0, s32, 0xC);
        temp_v0_2 = rand(temp_a0_3);
        color = 0x808080;
        temp_v0_2 = ((temp_v0_2 & 0x1FF) - 0x100) << 0xA;
        ASM_KEEP(temp_v0_2);
        temp_v1 = (u8 *)temp_v0 + 0x20;
        FIELD(temp_s2, s32, 0x14) = temp_v0_2;
        ASM_KEEP(temp_v1);
        FIELD(temp_v1, s16, 0xE) = 3;
        FIELD(temp_s0, s16, 0x1E) = 0x1000;
        FIELD(temp_s0, s16, 0x1C) = 0x1000;
        FIELD(temp_s0, void *, 8) = D_800F7944;
        FIELD(temp_s0, s8, 4) = 0;
        FIELD(temp_s0, s8, 5) = 0;
        FIELD(temp_s0, s32, 0xC) = color;
        FIELD(temp_s0, u16, 0x14) = FIELD(temp_s0, u16, 0x14) | 0xC;
    }
}
