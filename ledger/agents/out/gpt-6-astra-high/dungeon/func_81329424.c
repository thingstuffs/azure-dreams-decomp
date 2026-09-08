#include "common.h"

extern s32 D_800E296C[3];

/* Sets flag 0x40 in D_800E296C[0]. */
void func_80170C24(void) {
    D_800E296C[0] = (s32)(D_800E296C[0] | 0x40);
}
