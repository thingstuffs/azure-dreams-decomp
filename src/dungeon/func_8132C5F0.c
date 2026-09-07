#include "common.h"
#include "m2c_compat.h"

typedef struct S_80173DF0_0 {
    u8 pad_00[0x360C];
    u8 unk_360C;
} S_80173DF0_0;   /* temp_a0 in func_80173DF0 */

void func_80173DF0(s32 arg0) {
    S_80173DF0_0 *temp_a0;

    temp_a0 = arg0 + 0x80010000;
    temp_a0->unk_360C = (u8) (temp_a0->unk_360C + 1);
}
