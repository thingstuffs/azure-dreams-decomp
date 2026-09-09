#include "common.h"
#include "m2c_compat.h"

/* extern */
extern M2C_UNK D_800A0C30;

typedef struct S_800A0CC0_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
} S_800A0CC0_0;   /* arg0 in func_800A0CC0 */


s32 func_800352FC(S_800A0CC0_0 *, s32, s32, s32);
void func_800A0CC0(S_800A0CC0_0 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (func_800352FC(arg0, arg1, arg2, arg3) == 0) {
        arg0->unk_50 = &D_800A0C30;
    }
}
