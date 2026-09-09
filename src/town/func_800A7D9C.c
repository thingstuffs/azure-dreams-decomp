#include "common.h"
#include "m2c_compat.h"

/* extern */
extern M2C_UNK D_800A5340;

typedef struct S_800A54FC_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x16];
    M2C_UNK * unk_1C;
} S_800A54FC_0;   /* arg0 in func_800A54FC */


s32 func_800352FC(S_800A54FC_0 *, s32, s32, s32);
void func_800A54FC(S_800A54FC_0 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (func_800352FC(arg0, arg1, arg2, arg3) == 0) {
        arg0->unk_04 = 0x400;
        arg0->unk_1C = &D_800A5340;
    }
}
