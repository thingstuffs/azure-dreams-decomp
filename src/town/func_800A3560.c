#include "common.h"
#include "m2c_compat.h"

s32 func_800352FC();                                /* extern */
extern M2C_UNK D_800A0C30;

typedef struct S_800A0CC0_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
} S_800A0CC0_0;   /* arg0 in func_800A0CC0 */

void func_800A0CC0(S_800A0CC0_0 *arg0) {
    if (func_800352FC() == 0) {
        arg0->unk_50 = &D_800A0C30;
    }
}
