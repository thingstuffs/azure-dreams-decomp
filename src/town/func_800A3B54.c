#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A17CC();                            /* extern */

typedef struct S_800A12B4_0 {
    u8 pad_00[0x12];
    u16 unk_12;
    u8 pad_14[0x5A];
    u16 unk_6E;
} S_800A12B4_0;   /* arg0 in func_800A12B4 */

void func_800A12B4(S_800A12B4_0 *arg0) {
    u16 temp_v0;

    temp_v0 = arg0->unk_12 - 4;
    arg0->unk_12 = temp_v0;
    if ((s16) temp_v0 < 4) {
        arg0->unk_12 = 4U;
    }
    arg0->unk_6E = (u16) ((arg0->unk_6E + 1) & 0x7F);
    func_800A17CC();
}
