#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80039ACC_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x8];
    s32 unk_1C;
} S_80039ACC_0;   /* arg0 in func_80039ACC */


extern M2C_UNK func_80039AE8;

void func_80039ACC(S_80039ACC_0 *arg0) {
    arg0->unk_10 = &func_80039AE8;
    arg0->unk_1C = (s32) (arg0->unk_1C - 1);
}
