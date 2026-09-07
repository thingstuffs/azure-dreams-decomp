#include "common.h"

extern s32 D_800814A0[];

void func_7FDD3BE4(void *arg0) {
    void *temp_t0;
    void *var_a3;
    s32 var_a1;
    s32 var_a2;
    s32 temp_v1;
    s32 sum;

    temp_t0 = *(void **) ((s8 *) arg0 + 4);
    var_a2 = 2;
    *(s32 *) ((s8 *) arg0 + 8) = 0;
    var_a3 = (s8 *) temp_t0 + 4;
    do {
        var_a1 = *(s16 *) ((s8 *) var_a3 + 0xE);
        if (var_a1 >= 0x100) {
            var_a1 = 0xFF;
        }
        var_a3 = (s8 *) var_a3 - 2;
        temp_v1 = var_a2 * 8;
        var_a2 -= 1;
        sum = *(s32 *) ((s8 *) arg0 + 8);
        sum = sum + (var_a1 << temp_v1);
        *(s32 *) ((s8 *) arg0 + 8) = sum;
    } while (var_a2 >= 0);
    *(u16 *) ((s8 *) arg0 + 0x14) = *(u16 *) ((s8 *) temp_t0 + 0x14);
    if (*(s16 *) ((s8 *) temp_t0 + 0x16) & 0x8000) {
        *(u16 *) ((s8 *) arg0 - 2) = *(u16 *) ((s8 *) arg0 - 2) | 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
