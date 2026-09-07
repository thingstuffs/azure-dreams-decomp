#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80094984();           /* extern */
M2C_UNK func_80099754();                      /* extern */
extern M2C_UNK D_80097EFC;
extern M2C_UNK D_800D0170;

typedef struct S_80098ABC_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
    u8 pad_08[0x8];
    s16 unk_10;
} S_80098ABC_0;   /* arg0 in func_80098ABC */

typedef struct S_80098ABC_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80098ABC_1;   /* arg1 in func_80098ABC */

void func_80098ABC(S_80098ABC_0 *arg0, S_80098ABC_1 *arg1) {
    func_80094984(&D_800D0170, arg0);
    arg0->unk_04 = &D_80097EFC;
    func_80099754(arg1);
    arg1->unk_0C = 0xFFFE0000;
    arg1->unk_10 = 0x40000;
    arg1->unk_14 = 0xFFF90000;
    arg0->unk_10 = 0xE00;
}
