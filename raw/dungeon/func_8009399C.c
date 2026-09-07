#include "common.h"

extern s32 D_80082A38[];
extern s32 D_800DD718[];
extern u8 D_800E4958[];

void *func_800990FC(void) {
    s32 temp_a0;
    s32 var_a3;
    void *temp_v1;
    s32 *var_a2;
    s32 *table;

loop_0:
    var_a3 = 0xA;
    table = D_80082A38;
    var_a2 = table + 10;
    temp_a0 = D_800DD718[0] = (D_800DD718[0] + 1) % 6;
    temp_v1 = (temp_a0 * 0x138) + D_800E4958;
    do {
        var_a3 += 1;
        if (var_a2[18] == (s32)temp_v1) {
            goto loop_0;
        }
        var_a2 += 1;
    } while (var_a3 < 0xF);
    return temp_v1;
}

/* MECHANISM: A separate table-base local preserves retail's base materialization plus +0x28.
   Chained assignment holds the state base in $a1 and the value/remainder in $a0.
   The function remains a frameless leaf with the retail retry-loop CFG and store schedule. */
