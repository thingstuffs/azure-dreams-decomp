#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800789B8;

typedef struct S_80026CF0_0 {
    u8 pad_00[0xC];
    M2C_UNK ** unk_0C;
    s32 * unk_10;
} S_80026CF0_0;   /* arg0 in func_80026CF0 */

void func_80026CF0(S_80026CF0_0 *arg0, s32 arg1) {
    *arg0->unk_0C = &D_800789B8;
    *arg0->unk_10 = arg1;
}
