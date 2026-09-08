#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800B9204(); /* extern */
extern u8 D_80083160[];
extern u8 D_800D185C;
extern u8 D_800D185D;

void func_800B9260(void) {
    s32 *state = (s32 *) D_80083160;
    s32 flags = state[4];
    register s32 buttons ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 masked_buttons ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    if (flags < 0) {
        D_800D185C += 0x20;
    }
    if (flags & 0x20000000) {
        D_800D185C++;
    }
    D_800D185C %= 33;
    if (flags & 0x40000000) {
        D_800D185D += 0x42;
    }
    if (flags & 0x10000000) {
        D_800D185D++;
    }
    *(volatile u8 *) &D_800D185D = D_800D185D % 67;
    buttons = *(volatile s32 *) &state[2];
    masked_buttons = buttons & 0x500000;
    if (masked_buttons == 0x500000) {
        func_800B9204(D_800D185D);
    }
}

/* MECHANISM: Hold D_80083160 as a state base and cache flags for the $a3/$a2 lives.
   Type D_800D185C/D as direct bytes and honor func_800B9204's one-argument ABI.
   A volatile store/read seam plus split guarded $a0/$v0 lives fixes the final tail. */
