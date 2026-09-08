#include "common.h"

#define FIELD_U16(base, offset) (*(u16 *)((u8 *)(base) + (offset)))

extern s32 D_800814A0[3];

/* Decrement the countdown, setting completion flags on expiry or advancing the position. */
void func_800C907C(void *object, s32 *position) {
    u16 countdown;

    countdown = FIELD_U16(object, 0x6C) - 1;
    FIELD_U16(object, 0x6C) = countdown;
    if ((s16)countdown < 0) {
        FIELD_U16(object, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    } else {
        *position += 0xFFEAAAAB;
    }
}
