#include "common.h"
#include "shared/tile_object.h"

extern s8 find_active_rect_containing_point(u8, u8);
extern void update_actor_proximity_flag(void *source, void *state, s32 lower_limit, s32 upper_limit, s8 *result);
extern void update_all_actor_proximity_flags(s16 near_limit, s16 far_limit);

/* Updates the default or linked state and dispatches action (3, 6). */
void refresh_actor_proximity_state(u8 *context) {
    if ((context == 0) || (context[0x13] == 0)) {
        TileObject *state = &D_80082E80;

        state->unk_026 = find_active_rect_containing_point(state->tileX, state->tileY);
        update_all_actor_proximity_flags(3, 6);
        return;
    } else {
        TileObject *state = *(TileObject **)(context - 0x14);

        state->unk_026 = find_active_rect_containing_point(state->tileX, state->tileY);
        update_actor_proximity_flag(state, context, 3, 6, context + 0x9C);
    }
}
