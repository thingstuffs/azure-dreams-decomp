#include "common.h"

extern s8 D_800D1548[0x1549];

void func_800AC488(s16 arg0, s16 arg1, s8 arg2, s8 arg3) {
    s8 temp_a2;
    s8 temp_a3;

    D_800D1548[8] = arg2;
    D_800D1548[0] = arg2;
    temp_a2 = arg2 + 0x1F;
    D_800D1548[5] = arg3;
    D_800D1548[1] = arg3;
    temp_a3 = arg3 + 0x1F;
    D_800D1548[0xA] = temp_a2;
    D_800D1548[4] = temp_a2;
    D_800D1548[0xB] = temp_a3;
    D_800D1548[9] = temp_a3;
    *(s16 *)&D_800D1548[6] = arg0;
    *(s16 *)&D_800D1548[2] = arg1;
}
