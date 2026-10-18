#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
void func_800941D8(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2);    /* extern */
void call_the_handler_selects_nonzero_entry();  /* extern */
void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile();                     /* extern */
extern M2C_UNK D_800D00E0;


/* Decrements the state countdown and invokes its handler when it expires. */
void invoke_handler_when_countdown_expires(Rec_func_80094268_arg0 *state, s32 update_ctx, s32 handler_ctx) {
    s16 countdown;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(update_ctx);
    if (state->unk_0A.as_s16 == 0) {
        call_the_handler_selects_nonzero_entry(&D_800D00E0, state, handler_ctx);
    }
    countdown = (u16) state->unk_0A.as_s16 - 1;
    state->unk_0A.as_s16 = countdown;
    if ((countdown << 0x10) <= 0) {
        func_800941D8(state, update_ctx, handler_ctx);
    }
}
