#include "dungeon/actor/state.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"

extern s8 find_active_rect_containing_point(u8, u8);
extern void update_actor_proximity_flag(void *source, void *state, s32 lower_limit, s32 upper_limit, s8 *result);
extern void update_all_actor_proximity_flags(s16 near_limit, s16 far_limit);

/* Updates the default or linked state and dispatches action (3, 6). */
void refresh_actor_proximity_state(ActorRecord *context) {
    if ((context == 0) || (context->species == 0)) {
        TileObject *state = &reference_tile_object;

        state->room_index = find_active_rect_containing_point(state->tile_position.parts.tile_x, state->tile_position.parts.tile_y);
        update_all_actor_proximity_flags(3, 6);
        return;
    } else {
        SpriteFrameState *state = ((ObjectNodeHeader *)context)[-1].sprite;

        state->room_index = find_active_rect_containing_point(state->tile_x, state->tile_y);
        update_actor_proximity_flag(state, context, 3, 6, &context->unk_9C);
    }
}
