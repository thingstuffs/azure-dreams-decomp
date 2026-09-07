#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004E994();                         /* extern */

typedef struct S_800239B0_0 {
    u8 pad_00[0x1D8];
    s32 * unk_1D8;
} S_800239B0_0;   /* var_s0 in func_800239B0 */

void func_800239B0(void *arg0) {
    s32 *temp_v0;
    s32 var_s1;
    void *var_s0;

    var_s1 = 0;
    var_s0 = arg0;
    do {
        temp_v0 = ((S_800239B0_0 *)var_s0)->unk_1D8;
        var_s0 += 4;
        var_s1 += 1;
        func_8004E994(*temp_v0);
    } while (var_s1 < 3);
}
