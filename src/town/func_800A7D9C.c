#include "common.h"
#include "m2c_compat.h"

s32 func_800352FC();                                /* extern */
extern M2C_UNK D_800A5340;

typedef struct S_800A54FC_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x16];
    M2C_UNK * unk_1C;
} S_800A54FC_0;   /* arg0 in func_800A54FC */

void func_800A54FC(S_800A54FC_0 *arg0) {
    if (func_800352FC() == 0) {
        arg0->unk_04 = 0x400;
        arg0->unk_1C = &D_800A5340;
    }
}
