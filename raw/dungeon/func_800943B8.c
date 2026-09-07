#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((s8 *)(expr) + (offset)))

extern void func_800478B8(void *arg0);
extern void func_80099C3C(void);
typedef struct {
    s32 value;
    s32 pad[2];
} GlobalFlags;

extern GlobalFlags D_800814A0;

void func_80099B18(void *arg0, void *arg1, void *arg2)
{
    u16 temp_v0;
    u8 temp_v0_3;
    u8 temp_v0_4;
    u8 temp_v1_2;

    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        FIELD(arg0, u16, -2) =
            (s16)(FIELD(arg0, u16, -2) | 0x8000);
        D_800814A0.value |= 0x8000;
        func_80099C3C();
        return;
    }
    temp_v0 = FIELD(arg0, u16, 0x10) + 1;
    FIELD(arg0, u16, 0x10) = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        FIELD(arg2, u16, 0x14) =
            (u16)(FIELD(arg2, u16, 0x14) & 0xFF7F);
        func_800478B8(arg2);
    }
    if (FIELD(arg0, s16, 0xE) != 0) {
        FIELD(arg1, s32, 0) =
            (s32)(FIELD(arg1, s32, 0) + FIELD(arg1, s32, 0xC));
        FIELD(arg1, s32, 4) =
            (s32)(FIELD(arg1, s32, 4) + FIELD(arg1, s32, 0x10));
        FIELD(arg1, s32, 8) =
            (s32)(FIELD(arg1, s32, 8) + FIELD(arg1, s32, 0x14));
        FIELD(arg1, s32, 0xC) =
            (s32)(FIELD(arg1, s32, 0xC) - (FIELD(arg1, s32, 0xC) >> 2));
        FIELD(arg1, s32, 0x10) =
            (s32)(FIELD(arg1, s32, 0x10) - (FIELD(arg1, s32, 0x10) >> 2));
        FIELD(arg1, s32, 0x14) =
            (s32)(FIELD(arg1, s32, 0x14) - (FIELD(arg1, s32, 0x14) >> 2));
        temp_v0_3 = FIELD(arg2, u8, 0xC);
        temp_v1_2 = FIELD(arg2, u8, 0xD);
        FIELD(arg2, u8, 0xC) =
            (u8)(temp_v0_3 - (temp_v0_3 >> 1));
        temp_v0_4 = FIELD(arg2, u8, 0xE);
        FIELD(arg2, u8, 0xD) =
            (u8)(temp_v1_2 - (temp_v1_2 >> 1));
        FIELD(arg2, u8, 0xE) =
            (u8)(temp_v0_4 - (temp_v0_4 >> 1));
    }
}

/* MECHANISM: The three arguments stay live as s1/s0/s2, yielding the retail 0x20 frame and save order.
   Direct repeated s32 fields preserve the six-load update group and the required a1-to-a0 copy.
   The natural void tail call lets maspsx retain the global store in the retail jump delay slot. */
