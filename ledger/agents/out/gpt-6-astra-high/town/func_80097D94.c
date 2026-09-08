#include "common.h"

extern s32 D_800FE5C0[];

/* Clear global slot 5 and copy source slot 2 into global slot 2. */
void func_800954F4(s32 *source) {
    D_800FE5C0[5] = 0;
    D_800FE5C0[2] = source[2];
}
