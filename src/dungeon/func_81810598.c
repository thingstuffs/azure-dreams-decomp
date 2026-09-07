#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80025548;

typedef struct S_80025598_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x18];
    s32 unk_2C;
} S_80025598_0;   /* arg0 in func_80025598 */

void func_80025598(S_80025598_0 *arg0) {
    arg0->unk_2C = 0;
    arg0->unk_10 = &D_80025548;
}
