#include "common.h"

extern s32 D_80100DE0[];
extern u8 D_80100D98[];
/* Store the address of D_80100D98 in D_80100DE0. */
void func_800A5080(void) {
    *D_80100DE0 = (s32) D_80100D98;
}
