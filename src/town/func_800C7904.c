#include "common.h"

extern s32 func_800352FC(void);
extern void func_800A5160(s32 *arg0);
extern s32 D_80113208[];
extern u8 D_800C321C[];

void func_800C5064(void *arg0, void *arg1) {
    s32 *base;
    s32 value;

    if (func_800352FC() != 0) {
        D_80113208[0] = ((s32 *)arg1)[0];
        value = ((s32 *)arg1)[1];
        base = D_80113208;
        base[2] = 0;
        base[1] = value;
        func_800A5160(base);
        *(void **)((s8 *)arg0 - 0x10) = D_800C321C;
    }
}

/* MECHANISM: Long-lived arguments naturally select s1/s0 and the 0x20 frame.
   A one-read local preloads arg1[1] before materializing D_80113208.
   The wide-array extern emits the retail compiler-split hi/lo address form. */
