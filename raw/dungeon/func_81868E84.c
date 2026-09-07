#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern void *func_8003FC64(s32);
extern u8 D_80024384[];

void func_81868E84(void *arg0, void *arg1) {
    u32 temp_a0;
    u16 temp_v1;
    u16 temp_v1_2;
    u16 temp_v1_3;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != 0) {
        FIELD(temp_v0, void *, 0x10) = D_80024384;
        temp_v0_2 = temp_v0 + 0x20;
        FIELD(temp_v0, s16, 0x20) = 0;
        FIELD(temp_v0_2, s16, 2) = 0;
        temp_a0 = FIELD(arg0, u8, 9);
        FIELD(temp_v0_2, s16, 6) = 0;
        FIELD(temp_v0_2, s16, 8) = 0;
        FIELD(temp_v0_2, s16, 0xA) = 0;
        FIELD(temp_v0_2, void *, 0xC) = arg0;
        FIELD(temp_v0_2, s8, 0x10) = 0x40;
        FIELD(temp_v0_2, s16, 4) = temp_a0;
        temp_v0_3 = FIELD(temp_v0, void *, 8);
        temp_v1 = FIELD(arg1, u16, 2);
        FIELD(temp_v0_3, u16, 0xE) = temp_v1;
        FIELD(temp_v0_3, u16, 2) = temp_v1;
        temp_v1_2 = FIELD(arg1, u16, 6);
        FIELD(temp_v0_3, u16, 0x12) = temp_v1_2;
        FIELD(temp_v0_3, u16, 6) = temp_v1_2;
        temp_v1_3 = FIELD(arg1, u16, 0xA);
        FIELD(temp_v0_3, u16, 0x16) = temp_v1_3;
        FIELD(temp_v0_3, u16, 0xA) = temp_v1_3;
    }
}

/* MECHANISM: Hold arg0[9] in a u32 local after the first two zero stores.
   Its live range claims $a0, leaving the allocator result in $a1; u32 avoids
   the redundant andi and collapses the +1-word branch-displacement cascade. */
