/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

s32 func_80049790();                             /* extern */

typedef struct S_800AF254_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800AF254_0;   /* *arg1 in func_800AF254 */

typedef struct S_800AF254_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    s32 unk_20;
} S_800AF254_1;   /* temp_v1 in func_800AF254 */

void func_800AF254(s32 arg0, void **arg1) {
    s32 *var_s1;
    s32 temp_a0;
    s32 var_s0;
    s32 var_s2;
    S_800AF254_1 *temp_v1;

    var_s2 = 0x1A;
    var_s1 = arg0 + 0x68;
    var_s0 = ((S_800AF254_0 *)(*arg1))->unk_10 * 0xA;
loop_1:
    temp_v1 = *arg1;
    var_s2 += 1;
    if (var_s0 < temp_v1->unk_1C) {
        temp_a0 = *(s32 *)((var_s0 * 4) + temp_v1->unk_20);
        var_s0 += 1;
        *(*(s32 **)var_s1) = func_80049790(temp_a0);
        var_s1 += 1;
        if (var_s2 < 0x24) {
            goto loop_1;
        }
    }
}
