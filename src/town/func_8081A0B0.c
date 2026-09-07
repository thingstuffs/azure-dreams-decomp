#include "common.h"
#include "m2c_compat.h"

typedef struct S_800240B0_0 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800240B0_0;   /* arg2 in func_800240B0 */

void func_800240B0(s16 **arg0, M2C_UNK arg1, S_800240B0_0 *arg2) {
    s16 *temp_a0;

    temp_a0 = *arg0;
    if (*temp_a0 == 4) {
        arg2->unk_14 = (u16) (arg2->unk_14 | 0x80);
    }
    if (*temp_a0 == 0xFF) {
        arg2->unk_14 = (u16) (arg2->unk_14 & 0xFF7F);
    }
}
