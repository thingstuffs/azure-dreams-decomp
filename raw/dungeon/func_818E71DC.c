#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_800478B8(void *arg0);
extern void func_80024B48(void) __attribute__((noreturn));
extern s32 D_800814A0[3];

void func_800249DC(void *arg0, void *arg1, void *arg2) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 diff;
    u16 temp_v0;
    void *temp_ptr;

    temp_ptr = FIELD(arg0, void *, 0);
    FIELD(temp_ptr, s32, 0x10) =
        (s32)(FIELD(temp_ptr, s32, 0x10) | 0x8000);

    temp_v0 = FIELD(arg0, u16, 0x48) - 1;
    FIELD(arg0, u16, 0x48) = temp_v0;
    if ((temp_v0 << 16) > 0) {
        FIELD(arg0, s32, 0x1C) =
            (s32)(FIELD(arg0, s32, 0x1C) + FIELD(arg0, s32, 0x34));
        FIELD(arg0, s32, 0x20) =
            (s32)(FIELD(arg0, s32, 0x20) + FIELD(arg0, s32, 0x38));
        FIELD(arg0, s32, 0x24) =
            (s32)(FIELD(arg0, s32, 0x24) + FIELD(arg0, s32, 0x3C));
    }

    diff = FIELD(arg0, s32, 0x1C);
    temp_a0 = FIELD(arg1, s32, 0);
    diff -= temp_a0;
    FIELD(arg1, s32, 0) =
        (s32)(temp_a0 + (diff / 5));
    diff = FIELD(arg0, s32, 0x20);
    temp_a0_2 = FIELD(arg1, s32, 4);
    diff -= temp_a0_2;
    FIELD(arg1, s32, 4) =
        (s32)(temp_a0_2 + (diff / 5));
    diff = FIELD(arg0, s32, 0x24);
    temp_a0_3 = FIELD(arg1, s32, 8);
    diff -= temp_a0_3;
    FIELD(arg1, s32, 8) =
        (s32)(temp_a0_3 + (diff / 5));

    func_800478B8(arg2);
    if (FIELD(arg2, u16, 0x14) & 0x6000) {
        FIELD(arg2, s8, 4) = 0;
        FIELD(arg2, s8, 5) = 0;
    }

    if ((u8)FIELD(arg2, u8, 0xC) >= 0x60U) {
        FIELD(arg0, u16, -2) =
            (u16)(FIELD(arg0, u16, -2) | 0x8000);
        D_800814A0[0] = (s32)(D_800814A0[0] | 0x8000);
        func_80024B48();
        return;
    }

    FIELD(arg2, s32, 0xC) += 0xC0C0C;
}
