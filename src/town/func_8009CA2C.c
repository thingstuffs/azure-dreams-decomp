#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80099B00;

typedef struct S_8009A18C_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_8009A18C_0;   /* arg0 in func_8009A18C */

typedef struct S_8009A18C_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8009A18C_1;   /* arg1 in func_8009A18C */

void func_8009A18C(S_8009A18C_0 *arg0, S_8009A18C_1 *arg1) {
    arg0->unk_04 = &D_80099B00;
    arg1->unk_14 = 0xFFF60000;
}
