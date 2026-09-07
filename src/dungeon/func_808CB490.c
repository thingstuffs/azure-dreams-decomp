#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_8004D880();                             /* extern */
M2C_UNK func_800673A0();         /* extern */

typedef struct S_80123928_0 {
    u8 unk_00;
    u8 unk_01;
} S_80123928_0;   /* var_s0 in func_80123928 */

void func_80123928(u8 *arg0, s16 arg1, s16 arg2) {
    M2C_UNK sp10;
    s16 var_s1;
    u8 *var_s0;
    u8 temp_a0;
    u8 temp_v0;

    var_s0 = arg0;
    var_s1 = arg1;
    if (*var_s0 != 0) {
        do {
            temp_a0 = ((S_80123928_0 *)var_s0)->unk_00;
            temp_v0 = ((S_80123928_0 *)var_s0)->unk_01;
            var_s0 += 2;
            func_8004D91C(func_8004D880(temp_v0 | (temp_a0 << 8)) & 0xFF, &sp10);
            func_800673A0(&sp10, var_s1, arg2);
            var_s1 += 2;
        } while (*var_s0 != 0);
    }
}
