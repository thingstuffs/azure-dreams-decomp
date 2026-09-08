#include "common.h"
#include "m2c_compat.h"

/* extern */
M2C_UNK func_80093D48();    /* extern */

typedef struct S_80090F00_0 {
    s32 unk_00;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_80090F00_0;   /* arg0 in func_80090F00 */


M2C_UNK func_80090A74(S_80090F00_0 *, M2C_UNK, M2C_UNK);
void func_80090F00(S_80090F00_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 temp_s0;
    u16 temp_v0;

    temp_s0 = arg0->unk_00;
    func_80090A74(arg0, arg1, arg2);
    if (temp_s0 == arg0->unk_00) {
        temp_v0 = arg0->unk_0A - 1;
        arg0->unk_0A = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            func_80093D48(arg0, arg1, arg2);
        }
    }
}
