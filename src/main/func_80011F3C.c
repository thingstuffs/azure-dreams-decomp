#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80024A50();                      /* extern */
M2C_UNK func_80024E44();                      /* extern */

typedef struct S_80024F3C_0 {
    u8 pad_00[0x7C];
    s32 unk_7C;
    s32 unk_80;
} S_80024F3C_0;   /* temp_s0 in func_80024F3C */

void func_80024F3C(s32 arg0, s32 arg1, s32 arg2) {
    S_80024F3C_0 *temp_s0;

    if (arg0 != 0) {
        temp_s0 = arg0 + 0x20;
        temp_s0->unk_7C = arg1;
        temp_s0->unk_80 = arg2;
        func_80024E44(temp_s0);
        func_80024A50(temp_s0);
    }
}
