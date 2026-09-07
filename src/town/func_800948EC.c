#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800920BC();                            /* extern */
M2C_UNK func_8009431C();        /* extern */
M2C_UNK func_80094C1C();                         /* extern */
M2C_UNK func_80094C74();                      /* extern */
M2C_UNK func_80095388();                      /* extern */
M2C_UNK func_800954F4();                      /* extern */
M2C_UNK func_80095C80();                      /* extern */
M2C_UNK func_80096810();                      /* extern */
extern u8 D_800CFCEE;

typedef struct S_8009204C_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8009204C_0;   /* arg1 in func_8009204C */

void func_8009204C(s32 arg0, S_8009204C_0 *arg1, M2C_UNK arg2) {
    func_80096810(arg1);
    func_80095C80(arg1);
    func_80094C1C(arg0);
    func_80094C74(arg1);
    if (D_800CFCEE != 0) {
        arg1->unk_14 = 0;
        func_800954F4(arg1);
        func_800920BC();
        return;
    }
    func_80095388(arg1);
    if (arg1->unk_14 >= 0) {
        func_8009431C(arg0, arg1, arg2);
    }
}
