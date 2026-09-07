#include "common.h"

extern u16 D_80083460[];
extern s8 D_800DCF4F;

void func_800A2AE4(void) {
    u16 *p = (u16 *) &D_80083460;

    D_800DCF4F = 0;
    p[5]--;
}
