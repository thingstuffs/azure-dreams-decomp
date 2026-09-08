#include "common.h"

void func_800DC078(void *arg0, s32 arg1) {
    s32 value = (s16)arg1;

    if (value < 0x80) {
        s32 half = value / 2;

        value = half + 1;
    } else {
        value = 0x40;
    }
    ASM_KEEP(value);   /* MATCH pin: keeps a statement from moving across a call/branch */
    *(s8 *)((u8 *)arg0 + 2) = 0x57 - value;
    *(s8 *)((u8 *)arg0 + 0xA) = value;
}
