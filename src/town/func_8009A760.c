#include "common.h"
#include "m2c_compat.h"

/* extern */

typedef struct S_80097EC0_0 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80097EC0_0;   /* arg0 in func_80097EC0 */


M2C_UNK func_80098ABC(S_80097EC0_0 *, void *, s32);
void func_80097EC0(S_80097EC0_0 *arg0, void *arg1, s32 arg2) {
    u16 temp_v0;

    temp_v0 = arg0->unk_0A - 1;
    arg0->unk_0A = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_80098ABC(arg0, arg1, arg2);
    }
}
