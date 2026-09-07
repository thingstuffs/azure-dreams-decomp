#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80019B54();             /* extern */
M2C_UNK func_8001ACE8();                         /* extern */
s32 func_8001B0C8();                                /* extern */

typedef struct S_80017490_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_80017490_0;   /* arg0 in func_80017490 */

void func_80017490(S_80017490_0 *arg0, M2C_UNK arg1) {
    if (func_8001B0C8() != 0) {
        func_8001ACE8(arg0->unk_18);
    }
    func_80019B54(arg0, arg1);
}
