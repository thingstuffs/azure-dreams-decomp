#include "town/player/position_handlers.h"
#include "common.h"
#include "shared/town_handler_entries.h"
#include "shared/town_object.h"
#include "town/player.h"
#include "shared/sprite_frame_state.h"
void init_actor_action_state(TownObjectRecord *record, void *ptr, void *ptr2);    /* extern */
#include "town/player/call_the_handler_selects_nonzero_entry_api.h"  /* extern */
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"                     /* extern */


/* Decrements the state countdown and invokes its handler when it expires. */
void invoke_handler_when_countdown_expires(TownObjectRecord *state, ObjectPosition *update_ctx, SpriteFrameState *handler_ctx) {
    s16 countdown;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile((update_ctx));
    if (state->unk_0A == 0) {
        call_the_handler_selects_nonzero_entry(D_800D00E0, state, handler_ctx);
    }
    countdown = (u16) state->unk_0A - 1;
    state->unk_0A = countdown;
    if ((countdown << 0x10) <= 0) {
        init_actor_action_state(state, update_ctx, handler_ctx);
    }
}
