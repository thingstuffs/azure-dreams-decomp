#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80094984();  /* extern */
M2C_UNK func_80094C1C();                            /* extern */
extern M2C_UNK D_80092A84;
extern M2C_UNK D_800D0130;

typedef struct S_8009455C_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x3A];
    s16 unk_3E;
} S_8009455C_0;   /* arg0 in func_8009455C */

void func_8009455C(S_8009455C_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    arg0->unk_3E = 6;
    func_80094C1C();
    func_80094984(&D_800D0130, arg0, arg2);
    arg0->unk_00 = &D_80092A84;
}
