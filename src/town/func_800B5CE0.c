#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800B2DA0();                 /* extern */
M2C_UNK func_800B30D8();                            /* extern */
M2C_UNK func_800B32D4();                      /* extern */
M2C_UNK func_800B336C();                      /* extern */

typedef struct S_800B3440_0 {
    u8 pad_00[0xA8];
    s32 unk_A8;
} S_800B3440_0;   /* arg0 in func_800B3440 */

void func_800B3440(S_800B3440_0 *arg0) {
    func_800B30D8();
    func_800B336C(arg0);
    func_800B32D4(arg0);
    func_800B2DA0(arg0->unk_A8 + 0x68, arg0);
}
