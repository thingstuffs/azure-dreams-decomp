#include "common.h"

extern s16 D_80080B04;
extern u8 *D_80081508;
extern u8 D_8008333C[32];

void func_800AC37C(void) {
    u8 *var_a1;
    u16 *temp_v0;
    u16 temp_v1;
    u8 *pshift;
    u8 *base;

    pshift = D_8008333C;
    var_a1 = D_80081508;
    base = *(u8 **)pshift;
    if (*var_a1 != 0) {
        do {
            temp_v0 = (u16 *)(base +
                (var_a1[0] + (var_a1[1] << *(s16 *)(pshift + 0x14))) * 2);
            temp_v1 = *temp_v0;
            var_a1 += 4;
            *temp_v0 = temp_v1 & 0xBFFF;
        } while (*var_a1 != 0);
    }
    D_80080B04 = 0;
    *D_80081508 = 0;
}
