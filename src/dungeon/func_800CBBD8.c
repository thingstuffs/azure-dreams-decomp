#include "common.h"

extern s16 D_80080B00[8];
extern u8 D_8008333C[32];
extern u8 D_800E6000[16400];
extern u8 *D_80081508;

void func_800D1338(void) {
    u8 *var_a1;
    u8 *temp_v0;
    u16 temp_v1;
    u8 *pshift;

    pshift = D_8008333C;
    var_a1 = D_80081508;
    if (*var_a1 != 0) {
        do {
            temp_v0 = &D_800E6000[0x4000 + (var_a1[0] + (var_a1[1] << *(s16 *)(pshift + 0x14))) * 6];
            temp_v1 = *(u16 *)(temp_v0 + 4);
            var_a1 += 4;
            *(s16 *)(temp_v0 + 4) = (s16)(temp_v1 & 0xFF7F);
        } while (*var_a1 != 0);
    }
    *(s16 *)((u8 *)D_80080B00 + 4) = 0;
    *D_80081508 = 0;
}
