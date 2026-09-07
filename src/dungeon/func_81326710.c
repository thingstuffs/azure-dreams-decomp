#include "common.h"

extern s32 D_801749BC[];
extern s32 *D_80174704;
extern s32 D_80174CCC;
extern s16 D_80174CD0;

void func_8016DF10(s32 arg0) {
    s8 *temp_a1;

    D_80174CD0 = 0;
    temp_a1 = (s8 *)D_80174704 + 0x20;
    D_80174CCC = D_801749BC[arg0];
    temp_a1[0xB2] = 1;
    *(s16 *)(temp_a1 + 0xAC) = arg0;
}
