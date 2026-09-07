#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001CD7C_0 {
    u8 pad_00[0xA0];
    s32 unk_A0;
    s32 unk_A4;
    s32 unk_A8;
    s32 unk_AC;
} S_8001CD7C_0;   /* arg0 in func_8001CD7C */

void func_8001CD7C(S_8001CD7C_0 *arg0, s32 arg1) {
    s32 temp_v1;

    if (arg0 != NULL) {
        temp_v1 = arg0->unk_A8;
        arg0->unk_A4 = 0;
        arg0->unk_A0 = 3;
        arg0->unk_A8 = arg1;
        arg0->unk_AC = temp_v1;
    }
}
