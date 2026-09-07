#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009539C_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8009539C_0;   /* arg0 in func_8009539C */

void func_8009539C(S_8009539C_0 *arg0) {
    arg0->unk_00 = (s32) (arg0->unk_00 + arg0->unk_0C);
    arg0->unk_04 = (s32) (arg0->unk_04 + arg0->unk_10);
    arg0->unk_08 = (s32) (arg0->unk_08 + arg0->unk_14);
}
