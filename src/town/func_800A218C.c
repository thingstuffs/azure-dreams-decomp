#include "common.h"

extern s32 func_8009F750(void *arg0, void *arg1, s32 arg2);
extern s32 D_80010248[];
extern s8 D_80012D52[];

s32 func_8009F8EC(void *arg0) {
    s32 result;

    *((u8 *)arg0 + 3) |= 0x20;
    result = func_8009F750(arg0, (void *)0x80010248, 0x14);
    if (result != -1) {
        D_80012D52[0] = result;
    }
    return result;
}

/* MECHANISM: A full-word callee result avoids the spurious s8 sign-extension pair.
   The fixed 0x80010248 argument produces retail's lui/ori address construction.
   At 2.7.2-G0, the branch nop and $at macro store complete the 0x18-frame wrapper. */
