#include "common.h"
#include "m2c_compat.h"

extern void *D_80016000;

typedef struct S_80016D20_0 {
    u8 pad_00[0x18];
    s32 unk_18;
} S_80016D20_0;   /* base in func_80016D20 */

void func_80016D20(s32 arg0) {
    s32 *temp_v1;
    s32 temp_v0;
    s32 var_v0;
    S_80016D20_0 *base;

    if (arg0 != 1) {
        base = D_80016000;
        var_v0 = arg0;
        if (arg0 < 0) {
            var_v0 = arg0 + 0x1F;
        }
        temp_v0 = var_v0 >> 5;
        temp_v1 = (temp_v0 * 4) + base->unk_18;
        *temp_v1 &= ~(1 << (arg0 - (temp_v0 << 5)));
    }
}
