#include "common.h"
#include "shared/town_handler_entries.h"
#include "records/Rec_func_80094268_arg0.h"
void init_actor_action_state(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2);    /* extern */
#include "town/player/call_the_handler_selects_nonzero_entry_api.h"  /* extern */
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"                     /* extern */


/* Decrements the state countdown and invokes its handler when it expires. */
void invoke_handler_when_countdown_expires(Rec_func_80094268_arg0 *state, s32 update_ctx, s32 handler_ctx) {
    s16 countdown;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile((struct EntityRec *)(update_ctx));
    if (state->unk_0A.as_s16 == 0) {
        call_the_handler_selects_nonzero_entry(D_800D00E0, state, (void *)(handler_ctx));
    }
    countdown = (u16) state->unk_0A.as_s16 - 1;
    state->unk_0A.as_s16 = countdown;
    if ((countdown << 0x10) <= 0) {
        init_actor_action_state(state, update_ctx, handler_ctx);
    }
}
