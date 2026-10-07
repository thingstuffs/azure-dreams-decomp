#include "common.h"
#include "m2c_compat.h"
#include "shared/town_handler.h"

void func_800917EC(); /* extern */
extern M2C_UNK D_800917EC;
extern u8 D_800D0158;

typedef struct S_80091990_0 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80091990_0;   /* arg2 in func_80091990 */

/* Resets the handler when state flags are set, then invokes the base handler. */
void func_80091990(s32 **handler_slot, s32 context, S_80091990_0 *state) {
    if (state->unk_14 & 0x6000) {
        func_80094984((s32 *) &D_800D0158, (Rec_func_80094268_arg0 *) handler_slot, state);
        *handler_slot = &D_800917EC;
    }
    func_800917EC(handler_slot, context, state);
}
