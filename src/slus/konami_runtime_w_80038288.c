#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80038288_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x8];
    u8 * unk_1C;
} S_80038288_0;   /* arg0 in func_80038288 */


s32 func_80038240();                              /* extern */
s32 func_80053EF0();                         /* extern */
extern M2C_UNK func_800382F0;
extern M2C_UNK func_8003832C;

void func_80038288(S_80038288_0 *arg0) {
    M2C_UNK *var_v0;

    if (func_80053EF0(4) != 0x100) {
        if (func_80038240(*arg0->unk_1C) != 0) {
            var_v0 = &func_800382F0;
        } else {
            var_v0 = &func_8003832C;
        }
        arg0->unk_10 = var_v0;
    }
}
