#include "common.h"

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083350[5];
extern u8 D_800EA000[];

s32 func_8001CBD4(s32 inArg0, s32 inArg1, s32 inArg2)
{
    register s32 reg_a0 ASM_REG("$4");
    register s32 reg_a1 ASM_REG("$5");
    register s32 reg_a2 ASM_REG("$6");
    register s32 reg_v0 ASM_REG("$2");
    register u32 reg_t0 ASM_REG("$8");
    register u32 reg_t1 ASM_REG("$9");
    register u32 reg_t2 ASM_REG("$10");
    register u32 reg_t3 ASM_REG("$11");
    register s32 reg_t4 ASM_REG("$12");
    register s32 reg_t5 ASM_REG("$13");
    register s32 reg_v1 ASM_REG("$3");
    register u32 reg_a3 ASM_REG("$7");

    reg_a0 = inArg0;
    reg_a1 = inArg1;
    reg_a2 = inArg2;
    reg_t5 = reg_a0;
    ASM_KEEP_NV(reg_t5);
    reg_t4 = reg_a1;
    ASM_KEEP_NV(reg_t4);
    reg_t0 = 0x80080000;
    ASM_KEEP_NV(reg_t0);
    reg_v0 = reg_a2 << 16;
    reg_t1 = reg_v0 >> 16;
    ASM_KEEP_NV(reg_t1);
#ifdef NON_MATCHING
    reg_t3 = (u32)&D_8006CCD8;
#else
    reg_v0 = 0x80070000;
    ASM_KEEP_NV(reg_v0);
    reg_t3 = reg_v0 - 0x3328;
#endif
    ASM_KEEP_NV(reg_t3);
    reg_v1 = (s32)reg_t1 * 2;
    reg_a3 = reg_v1 + reg_t3;
    ASM_KEEP_NV(reg_a3);
#ifdef NON_MATCHING
    reg_t2 = (u32)&D_8006CCE8;
#else
    reg_v0 = 0x80070000;
    ASM_KEEP_NV(reg_v0);
    reg_t2 = reg_v0 - 0x3318;
#endif
    ASM_KEEP_NV(reg_t2);
    reg_v1 += reg_t2;
    reg_v0 = *(u16 *)reg_a3;
    reg_v1 = *(u16 *)reg_v1;
    reg_a0 += reg_v0;
    reg_a1 += reg_v1;
#ifdef NON_MATCHING
    reg_a3 = (u32)D_800EA000;
#else
    reg_v0 = 0x800F0000;
    ASM_KEEP_NV(reg_v0);
    reg_a3 = reg_v0 - 0x6000;
#endif
    reg_a1 = (s16)reg_a1;
    reg_a0 <<= 16;
    reg_v1 = *(s16 *)(reg_t0 + 0x3350);
    ASM_KEEP_NV(reg_v1);
    reg_a0 >>= 16;
    reg_a1 = (reg_a1 << reg_v1) + reg_a0;
    ASM_KEEP_NV(reg_a3);
    if (*(u16 *)(reg_a3 + reg_a1 * 6 + 4) != 0) {
        reg_a1 = 2;
        reg_t0 = reg_t1;
        reg_t1 = reg_a3;
        reg_a3 = reg_v1;
        do {
            reg_v0 = ((s32)reg_t0 + reg_a1) & 6;
            reg_v0 *= 2;
            reg_a0 = *(u16 *)(reg_v0 + reg_t3);
            reg_v1 = *(u16 *)(reg_v0 + reg_t2);
            reg_a0 = reg_t5 + reg_a0;
            reg_v1 = (s16)(reg_t4 + reg_v1);
            reg_v1 <<= reg_a3;
            reg_a0 = (s16)reg_a0;
            reg_v1 += reg_a0;
            if (*(u16 *)(reg_t1 + reg_v1 * 6 + 4) == 0) {
                return (reg_a2 + reg_a1) & 6;
            }
            reg_a1 += 4;
        } while (reg_a1 < 7);
    }
    return (s16)reg_a2;
}
