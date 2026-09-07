#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003F2A4();                         /* extern */

typedef struct S_800B6F54_0 {
    u8 pad_00[0xD0];
    s32 unk_D0;
    s32 unk_D4;
} S_800B6F54_0;   /* arg0 in func_800B6F54 */

s32 func_800B6F54(S_800B6F54_0 *arg0) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 var_v0;

    temp_a0 = arg0->unk_D0;
    var_v0 = 0;
    if (temp_a0 != 0) {
        func_8003F2A4(temp_a0);
        arg0->unk_D0 = 0;
        var_v0 = 1;
    }
    temp_a0_2 = arg0->unk_D4;
    if (temp_a0_2 != 0) {
        func_8003F2A4(temp_a0_2);
        arg0->unk_D4 = 0;
        var_v0 = 1;
    }
    return var_v0;
}
