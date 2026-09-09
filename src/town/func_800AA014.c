#include "common.h"
#include "m2c_compat.h"

/* extern */
extern M2C_UNK D_800A77D0;

typedef struct S_800A7774_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x3C];
    u16 unk_90;
} S_800A7774_0;   /* arg0 in func_800A7774 */


M2C_UNK func_80033D08(S_800A7774_0 *, s32);
void func_800A7774(S_800A7774_0 *arg0, s32 arg1) {
    u16 temp_v0;

    temp_v0 = arg0->unk_90 - 1;
    arg0->unk_90 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_80033D08(arg0, arg1);
        arg0->unk_90 = 0xAU;
        arg0->unk_50 = &D_800A77D0;
    }
}
