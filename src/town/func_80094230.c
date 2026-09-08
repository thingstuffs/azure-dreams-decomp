#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800917EC(); /* extern */
M2C_UNK func_80094984();       /* extern */
extern M2C_UNK D_800917EC;
extern M2C_UNK D_800D0158;

typedef struct S_80091990_0 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80091990_0;   /* arg2 in func_80091990 */

/* Resets the handler when state flags are set, then invokes the base handler. */
void func_80091990(M2C_UNK **handler_slot, M2C_UNK context, S_80091990_0 *state) {
    if (state->unk_14 & 0x6000) {
        func_80094984(&D_800D0158, handler_slot);
        *handler_slot = &D_800917EC;
    }
    func_800917EC(handler_slot, context, state);
}
