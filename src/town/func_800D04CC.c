#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80095388();                      /* extern */
M2C_UNK func_800CE04C();     /* extern */

typedef struct S_800CDC2C_0 {
    u8 pad_00[0x72];
    u16 unk_72;
} S_800CDC2C_0;   /* arg0 in func_800CDC2C */

typedef struct S_800CDC2C_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800CDC2C_1;   /* arg1 in func_800CDC2C */

void func_800CDC2C(S_800CDC2C_0 *arg0, S_800CDC2C_1 *arg1, M2C_UNK arg2) {
    arg0->unk_72 = (u16) (arg0->unk_72 + 0x400);
    arg1->unk_08 = (s32) (arg1->unk_08 + arg1->unk_14);
    func_80095388(arg1);
    if (arg1->unk_14 >= 0) {
        func_800CE04C(arg0, arg1, arg2);
    }
}
