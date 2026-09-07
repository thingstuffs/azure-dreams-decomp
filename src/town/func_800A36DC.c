#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A0B74();                 /* extern */
M2C_UNK func_800A0EB8();                            /* extern */
M2C_UNK func_800A12B4(); /* extern */
extern M2C_UNK D_800A08E8;
extern M2C_UNK D_80100B70;

typedef struct S_800A0E3C_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x18];
    u16 unk_6C;
} S_800A0E3C_0;   /* arg0 in func_800A0E3C */

typedef struct S_800A0E3C_1 {
    u8 pad_00[0x48];
    s32 unk_48;
} S_800A0E3C_1;   /* arg1 in func_800A0E3C */

void func_800A0E3C(S_800A0E3C_0 *arg0, S_800A0E3C_1 *arg1, M2C_UNK arg2, M2C_UNK arg3) {
    u16 temp_v0;

    func_800A12B4(&D_80100B70, arg2, arg3);
    temp_v0 = arg0->unk_6C - 1;
    arg0->unk_6C = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_800A0B74(arg0, arg1->unk_48);
        arg0->unk_50 = &D_800A08E8;
        func_800A0EB8();
    }
}
