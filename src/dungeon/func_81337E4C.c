#include "common.h"

extern s32 D_80173D5C;
extern s32 D_80175D50;
extern s32 D_80175DC4;
extern s16 D_80175DC8;

/* Select a table entry, reset its counter, and record the active index in object state. */
void func_8016EE4C(s32 table_index) {
    s8 *state;

    D_80175DC8 = 0;
    state = (s8 *)(D_80175D50 + 0x20);
    D_80175DC4 = ((s32 *)&D_80173D5C)[table_index];
    state[0xAF] = 1;
    state[0xAB] = table_index;
}
