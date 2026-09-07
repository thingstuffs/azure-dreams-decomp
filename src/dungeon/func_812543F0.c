#include "common.h"

extern s32 D_80173FBC[];
extern s32 *D_80174710;
extern s32 D_80174714;
extern s16 D_80174718;

void func_812543F0(s32 arg0) {
    s8 *temp_a1;

    D_80174718 = 0;
    temp_a1 = (s8 *)D_80174710 + 0x20;
    D_80174714 = D_80173FBC[arg0];
    temp_a1[0xBA] = 1;
    *(s16 *)(temp_a1 + 0xB8) = arg0;
}
