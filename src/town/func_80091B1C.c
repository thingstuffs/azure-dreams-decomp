#include "common.h"
#include "m2c_compat.h"

typedef struct S_8008F27C_0 {
    u8 pad_00[0x35];
    s8 unk_35;
} S_8008F27C_0;   /* arg0 in func_8008F27C */

typedef struct S_8008F27C_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_8008F27C_1;   /* arg1 in func_8008F27C */

void func_8008F27C(S_8008F27C_0 *arg0, S_8008F27C_1 *arg1, s32 arg2) {
    arg0->unk_35 = 1;
    arg1->unk_08 = (s32) (arg2 << 0x10);
    arg1->unk_14 = 0;
}
