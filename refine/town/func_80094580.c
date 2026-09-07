#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800941D8();    /* extern */
M2C_UNK func_80094984();  /* extern */
M2C_UNK func_80095C80();                     /* extern */
extern M2C_UNK D_800D00E0;

typedef struct S_80091CE0_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80091CE0_0;   /* arg0 in func_80091CE0 */

/* Decrements the state countdown and invokes its handler when it expires. */
void func_80091CE0(S_80091CE0_0 *state, M2C_UNK update_ctx, M2C_UNK handler_ctx) {
    s16 countdown;

    func_80095C80(update_ctx);
    if (state->unk_0A == 0) {
        func_80094984(&D_800D00E0, state, handler_ctx);
    }
    countdown = (u16) state->unk_0A - 1;
    state->unk_0A = countdown;
    if ((countdown << 0x10) <= 0) {
        func_800941D8(state, update_ctx, handler_ctx);
    }
}
