#include "common.h"

extern s16 func_800BCB04(u16, u16, s16);
extern s16 D_80026664;
extern s32 D_800814A0[3];

__asm__(".set D_80026664, 0x80026664");

/* Adjust height conditionally and set flags when the countdown reaches zero or below. */
void func_81875A78(void *state, s16 *position)
{
    s16 *state_words = state;
    s16 countdown;

    D_80026664 = 1;
    if (position[5] < func_800BCB04((u16)position[1], (u16)position[3], position[5] + 2)) {
        ((s32 *)position)[2] += *(s32 *)((u8 *)state + 0x48);
    }

    countdown = (u16)state_words[25] - 4;
    state_words[25] = countdown;
    if ((countdown << 16) <= 0) {
        ((u16 *)state_words)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
