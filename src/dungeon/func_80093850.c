#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)

extern M2C_UNK D_8001004C;

typedef struct S_80098FB0_0 {
    u8 pad_00[0x249];
    u8 unk_249;
} S_80098FB0_0;   /* var_a0 in func_80098FB0 */

s32 func_80098FB0(void) {
    s8 *var_a0;
    s32 var_a1;
    s32 var_v0;
    s32 var_v1;

    var_a1 = -1;
    var_v1 = 0x13;
    var_a0 = (s8 *)0x8001004C;
for (;;) {
loop_1:
    if (((S_80098FB0_0 *)var_a0)->unk_249 == 0) {
        var_a1 = var_v1;
    } else if (var_a1 >= 0) {
        break;
    }
    var_v1 -= 1;
    var_a0 -= 4;
    if (var_v1 < 0) {
        break;
    }
    goto loop_1;
}
done:
    var_v0 = var_a1 << 0x10;
    return var_v0 >> 0x10;
}
