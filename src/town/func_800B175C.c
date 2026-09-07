#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800AEE98();                      /* extern */

typedef struct S_800AEEBC_0 {
    u8 pad_00[0x28];
    s32 unk_28;
    u8 pad_2C[0x8];
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
} S_800AEEBC_0;   /* arg0 in func_800AEEBC */

void func_800AEEBC(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    ((S_800AEEBC_0 *)arg0)->unk_3C = arg1;
    ((S_800AEEBC_0 *)arg0)->unk_34 = arg2;
    ((S_800AEEBC_0 *)arg0)->unk_28 = arg3;
    ((S_800AEEBC_0 *)arg0)->unk_38 = arg4;
    func_800AEE98(arg0 + 0x40);
}
