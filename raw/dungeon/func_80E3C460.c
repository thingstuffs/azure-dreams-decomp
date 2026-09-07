#include "common.h"

extern void func_80175D6C() __attribute__((noreturn));
extern s32 D_800814A0;
extern s16 D_80083228;

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

void func_80175C60(void *arg0, void *arg1, void *arg2)
{
    register void *arg1_pinned ASM_REG("$5") = arg1;
    s32 temp_v1_wide;
    s32 temp_a0;
    s32 temp_a2;
    s32 temp_v0_2;
    s32 temp_v1;
    u16 temp_v0;

    ASM_KEEP(arg1_pinned);
    FIELD(arg1_pinned, s32, 0) += FIELD(arg1_pinned, s32, 0xC);
    FIELD(arg1_pinned, s32, 4) += FIELD(arg1_pinned, s32, 0x10);
    FIELD(arg1_pinned, s32, 8) += FIELD(arg1_pinned, s32, 0x14);
    temp_v1 = FIELD(arg1_pinned, s32, 0xC);
    temp_a0 = temp_v1 >> 5;
    temp_a2 = FIELD(arg1_pinned, s32, 0x10);
    temp_v0_2 = temp_a2;
    ASM_KEEP(temp_v0_2);
    FIELD(arg1_pinned, s32, 0xC) = temp_v1 + temp_a0;
    ASM_KEEP(temp_v0_2);
    temp_v0_2 += temp_v0_2 >> 5;
    FIELD(arg1_pinned, s32, 0x10) = temp_v0_2;
    temp_v0 = FIELD(arg0, u16, 0x20) - 1;
    FIELD(arg0, u16, 0x20) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        func_80175D6C(temp_a0, arg1_pinned, temp_a2, arg2);
    }
    FIELD(arg2, u16, 0x1C) += 0x80;
    FIELD(arg2, u16, 0x1E) += 0x80;
    FIELD(arg2, u16, 0x1A) += 0x40;
    {
        register s32 temp_v1_2 ASM_REG("$4");

        temp_v1_wide = ((((s32)(D_80083228 + *FIELD(arg0, s16 *, 0) + 0x100) >> 9) & 7) + 2) << 9;
        temp_v1_2 = temp_v1_wide;
        ASM_KEEP(temp_v1_2);
        FIELD(arg2, s16, 0x18) = temp_v1_wide;
        if ((temp_v1_2 == 0x400) || (temp_v1_2 == 0xC00)) {
            FIELD(arg2, s16, 0x18) = temp_v1_wide + 0x100;
        }
    }
}
