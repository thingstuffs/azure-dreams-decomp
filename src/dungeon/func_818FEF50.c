#include "common.h"

extern s16 D_80025E80;
extern s32 D_800814A0;

void func_818FEF50(void *arg0) {
    u16 *flags = (u16 *)arg0 - 1;

    D_80025E80 = 1;
    *flags |= 0x8000;
    D_800814A0 |= 0x8000;
}
