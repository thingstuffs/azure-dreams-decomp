#include "common.h"
#include "m2c_compat.h"

s32 func_8008EFA0();                                /* extern */

typedef struct S_8008F01C_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    s8 unk_14;
    s8 unk_15;
} S_8008F01C_0;   /* arg0 in func_8008F01C */

void func_8008F01C(S_8008F01C_0 *arg0, s32 arg1, s32 arg2) {
    if (func_8008EFA0() != 0) {
        arg0->unk_08 = arg1;
        arg0->unk_0C = arg2;
        arg0->unk_15 = 1;
        arg0->unk_14 = 0;
    }
}
