#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800661B0(); /* extern */
s32 func_80122FA8();                             /* extern */

typedef struct S_801239B8_0 {
    u8 unk_00;
    u8 unk_01;
} S_801239B8_0;   /* var_s0 in func_801239B8 */

void func_801239B8(u8 *arg0, s16 arg1, s16 arg2) {
    s16 var_s1;
    s32 temp_v0_2;
    u8 *var_s0;
    u8 temp_a0;
    u8 temp_v0;

    var_s0 = arg0;
    var_s1 = arg1;
    if (*var_s0 != 0) {
        do {
            temp_a0 = ((S_801239B8_0 *)var_s0)->unk_00;
            temp_v0 = ((S_801239B8_0 *)var_s0)->unk_01;
            var_s0 += 2;
            temp_v0_2 = func_80122FA8(temp_v0 | (temp_a0 << 8));
            if (temp_v0_2 != 0) {
                func_800661B0(temp_v0_2, 0, 0, var_s1, (s32) arg2, 0xC, 0x10);
                var_s1 += 3;
            }
        } while (*var_s0 != 0);
    }
}
