#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800948DC();                            /* extern */
M2C_UNK func_80094984(); /* extern */
extern M2C_UNK D_80092CD4;
extern M2C_UNK D_800D0140;

typedef struct S_800945B8_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800945B8_0;   /* arg1 in func_800945B8 */

void func_800945B8(M2C_UNK **arg0, S_800945B8_0 *arg1, M2C_UNK arg2) {
    func_800948DC();
    arg1->unk_14 = 0xFFEF0000;
    func_80094984(&D_800D0140, arg0, arg2);
    *arg0 = &D_80092CD4;
}
