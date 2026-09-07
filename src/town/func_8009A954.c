#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80098928();                            /* extern */

typedef struct S_800980B4_0 {
    u8 pad_00[0xA];
    u16 unk_0A;
    u8 pad_0C[0x4];
    s16 unk_10;
} S_800980B4_0;   /* arg0 in func_800980B4 */

void func_800980B4(S_800980B4_0 *arg0) {
    u16 temp_v0;

    temp_v0 = arg0->unk_0A - 1;
    arg0->unk_0A = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_80098928();
        arg0->unk_10 = 0x400;
    }
}
