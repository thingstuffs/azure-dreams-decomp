#include "common.h"

extern s32 func_80042900(void *, s8);

extern s32 D_800DCF08[];
extern s32 D_800DCF3C;
extern s32 D_800DCF44;
extern s32 D_800DCF48;

s32 func_800A652C(void *arg0) {
    s32 result;
    s32 index;
    s32 seven;
    s32 value;

    if (*(u8 *)((u8 *)arg0 + 0x13) == 0) {
        index = 14;
        goto init_loop;
    }
    if (*(u8 *)((u8 *)arg0 + 0x25) == 0) {
        value = D_800DCF44;
        goto done;
    }
    index = 14;
    if (*(s32 *)((u8 *)arg0 + 0x1C) & 0x20000) {
        goto init_loop;
    }
    value = D_800DCF3C;
    goto done;

return_special:
    value = D_800DCF48;
    goto done;

return_indexed:
    value = D_800DCF08[index];
    goto done;

init_loop:
    seven = 7;
loop:
    result = (s16)func_80042900(arg0, index);
    if (result > 0) {
        if (index == seven) {
            goto return_special;
        }
    }
    if (result != 0) {
        goto return_indexed;
    }
    index--;
    if (index >= 0) {
        goto loop;
    }
    value = D_800DCF08[0];

done:
    return value;
}

/* MECHANISM: True-space local epilogue edges yield the 0x20 frame and s1/s0/s2 holds.
   Split index=14 assignments retain the second li in the flag-branch delay slot.
   An s32 result assigned from the s16 call cast keeps v0 live through both tests. */
