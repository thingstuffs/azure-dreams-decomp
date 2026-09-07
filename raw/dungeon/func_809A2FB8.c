#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((s8 *)(ptr) + (offset)))

extern s32 D_800814A0[3];

void func_801747B8(void *arg0, void *arg1, void *arg2)
{
    s16 state;
    s32 count;
    u8 *dst;

    FIELD(arg2, s32, 8) = FIELD(FIELD(arg0, void *, 0x18), s32, 8);
    FIELD(arg2, u16, 0x14) =
        FIELD(FIELD(arg0, void *, 0x18), u16, 0x14) | 0xC;

    if (FIELD(arg0, u8, 0x17) == 0) {
        state = FIELD(arg0, s16, 0x34);
        if (FIELD(arg2, u8, 0xC) < (0x80 >> state)) {
            FIELD(arg2, s32, 0xC) += 0x101010;
            goto continuation;
        }
        FIELD(arg0, u8, 0x17)++;
        goto continuation;
    }

    if (FIELD(arg2, u8, 0xC) == 0) {
        goto no_adjustment;
    }
    FIELD(arg2, s32, 0xC) += -0x80808;
    goto continuation;

no_adjustment:
    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0[0] |= 0x8000;

continuation:
    FIELD(arg1, u16, 2) = FIELD(arg0, u16, 0x20);
    FIELD(arg1, u16, 6) = FIELD(arg0, u16, 0x26);
    FIELD(arg1, u16, 0xA) = FIELD(arg0, u16, 0x2C);

    count = 0;
    if (FIELD(arg0, s16, 0x34) > 0) {
        do {
            FIELD(arg0, u16, count * 2 + 0x20) = FIELD(arg0, u16, count * 2 + 0x22);
            FIELD(arg0, u16, count * 2 + 0x26) = FIELD(arg0, u16, count * 2 + 0x28);
            FIELD(arg0, u16, count * 2 + 0x2C) = FIELD(arg0, u16, count * 2 + 0x2E);
            count++;
        } while (count < FIELD(arg0, s16, 0x34));
    }

    dst = (u8 *)(count * 2 + (s32)(u32)arg0);
    FIELD(dst, u16, 0x20) = FIELD(FIELD(arg0, void *, 0x1C), u16, 2);
    FIELD(dst, u16, 0x26) = FIELD(FIELD(arg0, void *, 0x1C), u16, 6);
    FIELD(dst, u16, 0x2C) = FIELD(FIELD(arg0, void *, 0x1C), u16, 0xA);
}
