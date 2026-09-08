#include "common.h"
#include "m2c_compat.h"

s32 func_800A639C();                             /* extern */
M2C_UNK func_800A63C8();                /* extern */
extern s32 D_80100E2C[1];

/* Resolve the low-byte index, apply its value, and clear the pending state. */
void func_800A643C(s32 index, M2C_UNK value) {
    s32 *pending_state;
    func_800A63C8(func_800A639C(index & 0xFF), value);
    pending_state = D_80100E2C;
    *pending_state = 0;
}
