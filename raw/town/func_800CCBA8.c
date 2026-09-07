#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_800C4174(void *arg0, void *arg1, s32 arg2);
extern void func_800CA3D4(void);

void func_800CA308(void *arg0, void *arg1, s32 arg2) {
    s32 delta;
    s32 delta2;
    s32 delta3;
    u16 timer;

    timer = FIELD(arg0, u16, 0x6C) - 1;
    FIELD(arg0, u16, 0x6C) = timer;
    if ((timer << 16) <= 0) {
        func_800C4174(arg0, arg1, arg2);
        FIELD(arg1, u16, 2) = FIELD(arg0, u16, 0x84);
        FIELD(arg1, s16, 6) = FIELD(arg0, u16, 0x86);
        FIELD(arg1, s16, 0xA) = 0;
        func_800CA3D4();
        return;
    }

    delta = (s16)FIELD(arg0, u16, 0x84) -
            (s16)FIELD(arg1, u16, 2);
    if (delta < 0) {
        delta += 7;
    }
    FIELD(arg1, u16, 2) =
        (u16)(FIELD(arg1, u16, 2) + (delta >> 3));

    delta2 = (s16)FIELD(arg0, u16, 0x86) - FIELD(arg1, s16, 6);
    if (delta2 < 0) {
        delta2 += 7;
    }
    FIELD(arg1, s16, 6) =
        (s16)((u16)FIELD(arg1, s16, 6) + (delta2 >> 3));

    delta3 = -FIELD(arg1, s16, 0xA);
    if (delta3 < 0) {
        delta3 += 7;
    }
    FIELD(arg1, s16, 0xA) =
        (s16)((u16)FIELD(arg1, s16, 0xA) + (delta3 >> 3));
}
