#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80019B54();             /* extern */
M2C_UNK func_8001ACE8();                         /* extern */
s32 func_8001ADE0();                         /* extern */

typedef struct S_80016F2C_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_80016F2C_0;   /* arg0 in func_80016F2C */

void func_80016F2C(S_80016F2C_0 *arg0, M2C_UNK arg1) {
    if (func_8001ADE0(0x1451) != 0) {
        func_8001ACE8(arg0->unk_18);
    }
    func_80019B54(arg0, arg1);
}
