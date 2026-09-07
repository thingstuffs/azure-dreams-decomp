#include "common.h"
#include "m2c_compat.h"

s32 func_800AB378();                                /* extern */
s32 func_800AD9B4();                /* extern */
extern M2C_UNK D_800D4494;

typedef struct S_800D45D0_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
} S_800D45D0_0;   /* arg0 in func_800D45D0 */

void func_800D45D0(S_800D45D0_0 *arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {
    if ((func_800AB378() != 0) && ((func_800AD9B4(arg2, arg3) << 0x10) > 0)) {
        arg0->unk_8C = &D_800D4494;
    }
}
