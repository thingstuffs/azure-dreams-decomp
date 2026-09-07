#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800E2970;

typedef struct S_80017560_0 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_80017560_0;   /* var_v0 in func_80017560 */

void func_80017560(void) {
    s8 *var_v0;
    s32 var_v1;

    var_v0 = &D_800E2970;
    var_v1 = 0x24;
    do {
        ((S_80017560_0 *)var_v0)->unk_0C = 0;
        var_v1 -= 1;
        var_v0 += 0x14;
    } while (var_v1 > 0);
}
