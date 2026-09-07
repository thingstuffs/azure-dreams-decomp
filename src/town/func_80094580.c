#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800941D8();    /* extern */
M2C_UNK func_80094984();  /* extern */
M2C_UNK func_80095C80();                     /* extern */
extern M2C_UNK D_800D00E0;

typedef struct S_80091CE0_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80091CE0_0;   /* arg0 in func_80091CE0 */

void func_80091CE0(S_80091CE0_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s16 temp_v0;

    func_80095C80(arg1);
    if (arg0->unk_0A == 0) {
        func_80094984(&D_800D00E0, arg0, arg2);
    }
    temp_v0 = (u16) arg0->unk_0A - 1;
    arg0->unk_0A = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_800941D8(arg0, arg1, arg2);
    }
}
