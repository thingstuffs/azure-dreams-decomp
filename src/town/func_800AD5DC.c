#include "common.h"

extern void func_800AAE30(void *, s32, s32 *);
extern s32 D_800834B8;
extern u8 D_800AA5F8[];
extern s32 *D_800D0B14;
extern u16 D_80100D62;

void func_800AAD3C(void *arg0, s32 arg1, s32 *arg2) {
    u16 value = D_80100D62;
    s32 *src = D_800D0B14;

    *(u16 *)((u8 *)arg0 + 0x72) = value;
    if (src != 0) {
        arg2[0] = src[0];
        arg2[1] = src[1];
        arg2[2] = src[2];
    }
    
    if (D_800834B8 != (s32)D_800AA5F8) {
        func_800AAE30(arg0, arg1, arg2);
    }
}

/* MECHANISM: Preserve the middle ABI argument through the copy so $a1 is not recycled.
   Load the u16 before holding D_800D0B14; the retail frame is 0x18 with only $ra saved. */
