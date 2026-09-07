#include "common.h"

extern s16 D_800D4268[];
extern s16 D_800D4258[];
extern s8 D_80080A88[];

void func_800C0FA4(void) {
    s16 *p;

    D_800D4268[0] = -1;
    p = D_800D4268;
    p[1] = -1;
    p[2] = -1;
    p[3] = -1;

    D_800D4258[0] = -1;
    p = D_800D4258;
    p[1] = -1;
    p[2] = -1;
    p[3] = -1;

    D_80080A88[0] = 0;
}
