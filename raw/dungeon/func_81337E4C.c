#include "common.h"

extern s32 D_80173D5C;
extern s32 D_80175D50;
extern s32 D_80175DC4;
extern s16 D_80175DC8;

void func_8016EE4C(s32 arg0) {
    s8 *state;

    D_80175DC8 = 0;
    state = (s8 *)(D_80175D50 + 0x20);
    D_80175DC4 = ((s32 *)&D_80173D5C)[arg0];
    state[0xAF] = 1;
    state[0xAB] = arg0;
}
