#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80090A74();                            /* extern */
M2C_UNK func_80093D48();      /* extern */

typedef struct S_80090DF0_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_80090DF0_0;   /* arg1 in func_80090DF0 */

void func_80090DF0(s32 *arg0, S_80090DF0_0 *arg1, M2C_UNK arg2) {
    s32 temp_s0;

    temp_s0 = *arg0;
    func_80090A74();
    if ((temp_s0 == *arg0) && (arg1->unk_0C == 0) && (arg1->unk_10 == 0)) {
        func_80093D48(arg0, arg1, arg2);
    }
}
