#include "common.h"

extern s32 D_80100DE0[];
extern s32 D_800D0C48[];

void func_800A50E0(void) {
    s32 temp_v1;
    s32 temp_a0;

    temp_v1 = D_80100DE0[9];
    temp_a0 = D_80100DE0[10];
    D_80100DE0[9] = 0;
    D_80100DE0[10] = 0;
    D_800D0C48[0] = temp_v1;
    D_800D0C48[1] = temp_a0;
}
