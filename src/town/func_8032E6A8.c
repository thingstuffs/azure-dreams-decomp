/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

extern s8 D_80016000[];

typedef struct S_80018EA8_0 {
    u8 pad_00[0x38];
    s32 unk_38;
} S_80018EA8_0;   /* *(s8 **)D_80016000 in func_80018EA8 */

void func_80018EA8(void) {
    s8 *temp_a2;
    s32 temp_v1;
    s32 var_a0;
    s32 var_a1;
    s32 var_a3;

    var_a1 = 0;
    temp_a2 = (s8 *)((S_80018EA8_0 *)(*(s8 **)D_80016000))->unk_38 + 0x29C;
    var_a0 = var_a1;
    var_a3 = -1;
loop_1:
    temp_v1 = *(s32 *)(temp_a2 + (var_a0 * 4));
    if (temp_v1 != 0) {
        if (temp_v1 != var_a3) {
            if (var_a0 != var_a1) {
                *(s32 *)(temp_a2 + (var_a1 * 4)) = temp_v1;
            }
            var_a1 += 1;
        }
        var_a0 += 1;
        if (var_a0 < 0x14) {
            goto loop_1;
        }
    }
    *(s32 *)(temp_a2 + (var_a1 * 4)) = 0;
}
