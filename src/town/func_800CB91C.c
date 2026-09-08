#include "common.h"

#define FIELD_U16(base, offset) (*(u16 *)((u8 *)(base) + (offset)))

extern s32 D_800814A0[3];

void func_800C907C(void *arg0, s32 *arg1) {
    u16 value;

    value = FIELD_U16(arg0, 0x6C) - 1;
    FIELD_U16(arg0, 0x6C) = value;
    if ((s16)value < 0) {
        FIELD_U16(arg0, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    } else {
        *arg1 += 0xFFEAAAAB;
    }
}
