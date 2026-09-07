#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800917EC(); /* extern */
M2C_UNK func_80094984();       /* extern */
extern M2C_UNK D_800917EC;
extern M2C_UNK D_800D0158;

typedef struct S_80091990_0 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80091990_0;   /* arg2 in func_80091990 */

void func_80091990(M2C_UNK **arg0, M2C_UNK arg1, S_80091990_0 *arg2) {
    if (arg2->unk_14 & 0x6000) {
        func_80094984(&D_800D0158, arg0);
        *arg0 = &D_800917EC;
    }
    func_800917EC(arg0, arg1, arg2);
}
