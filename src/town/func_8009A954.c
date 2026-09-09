#include "common.h"
#include "m2c_compat.h"

/* extern */

typedef struct S_800980B4_0 {
    u8 pad_00[0xA];
    u16 unk_0A;
    u8 pad_0C[0x4];
    s16 unk_10;
} S_800980B4_0;   /* arg0 in func_800980B4 */


M2C_UNK func_80098928(S_800980B4_0 *, s32, s32);
void func_800980B4(S_800980B4_0 *arg0, s32 arg1, s32 arg2) {
    u16 temp_v0;

    temp_v0 = arg0->unk_0A - 1;
    arg0->unk_0A = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_80098928(arg0, arg1, arg2);
        arg0->unk_10 = 0x400;
    }
}
