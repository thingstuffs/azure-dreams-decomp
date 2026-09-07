#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80035ABC_0 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80035ABC_0;   /* arg1 in func_80035ABC */

typedef struct S_80035ABC_1 {
    u8 pad_00[0x68];
    M2C_UNK * unk_68;
} S_80035ABC_1;   /* arg0 in func_80035ABC */


extern M2C_UNK func_80035AF8;

void func_80035ABC(S_80035ABC_1 *arg0, S_80035ABC_0 *arg1) {
    u16 temp_v0;

    temp_v0 = arg1->unk_02 - 0x10;
    arg1->unk_02 = temp_v0;
    if ((s16) temp_v0 < 2) {
        arg1->unk_02 = 2U;
        arg0->unk_68 = &func_80035AF8;
    }
}
