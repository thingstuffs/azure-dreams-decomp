#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800AF254();                 /* extern */
M2C_UNK func_800AF520();                            /* extern */
M2C_UNK func_800AF674();                      /* extern */
M2C_UNK func_800AF784();                      /* extern */
M2C_UNK func_800AF858();                 /* extern */

typedef struct S_800AF860_0 {
    u8 pad_00[0xA8];
    s32 unk_A8;
} S_800AF860_0;   /* arg0 in func_800AF860 */

void func_800AF860(S_800AF860_0 *arg0) {
    func_800AF520();
    func_800AF784(arg0);
    func_800AF674(arg0);
    func_800AF254(arg0->unk_A8, arg0);
    func_800AF858(arg0->unk_A8, arg0);
}
