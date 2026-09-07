#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800920F4;

typedef struct S_8009431C_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x6];
    s16 unk_0A;
} S_8009431C_0;   /* arg0 in func_8009431C */

void func_8009431C(S_8009431C_0 *arg0) {
    arg0->unk_00 = &D_800920F4;
    arg0->unk_0A = 0;
}
