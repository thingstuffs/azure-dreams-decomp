#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C4174();    /* extern */
M2C_UNK func_800CB73C();                            /* extern */
M2C_UNK func_800CBB68();                /* extern */

typedef struct S_800CB7EC_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
    u8 pad_6E[0x1A];
    s16 unk_88;
    s16 unk_8A;
    u8 pad_8C[0xA];
    s8 unk_96;
} S_800CB7EC_0;   /* arg0 in func_800CB7EC */

void func_800CB7EC(S_800CB7EC_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    u16 temp_v0;

    temp_v0 = arg0->unk_6C - 1;
    arg0->unk_6C = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_800CB73C();
        func_800CBB68(arg0->unk_96, arg0->unk_88, arg0->unk_8A);
        func_800C4174(arg0, arg1, arg2);
    }
}
