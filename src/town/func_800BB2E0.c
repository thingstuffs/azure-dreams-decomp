#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B8A40_0 {
    u8 pad_00[0x3608];
    u8 unk_3608;
    u8 pad_3609[0x1];
    u8 unk_360A;
} S_800B8A40_0;   /* temp_v0_2 in func_800B8A40 */

void func_800B8A40(void) {
    volatile u8 *var_v1;
    s32 var_a0;
    s32 var_a0_2;
    u8 temp_v0;
    u8 temp_v1;
    S_800B8A40_0 *temp_v0_2;

    var_a0 = 0;
    var_v1 = (u8 *)0x80010000;
    do {
        temp_v0 = var_v1[0x33A5];
        if (temp_v0 != 0) {
            var_v1[0x33A4] = temp_v0;
            var_v1[0x33A5] = 0;
        }
        var_a0 += 1;
        var_v1 += 2;
    } while (var_a0 < 0x22);
    var_a0_2 = 0;
    do {
        temp_v0_2 = var_a0_2 + 0x80010000;
        temp_v1 = temp_v0_2->unk_360A;
        var_a0_2 += 1;
        temp_v0_2->unk_3608 = temp_v1;
    } while (var_a0_2 < 2);
}
