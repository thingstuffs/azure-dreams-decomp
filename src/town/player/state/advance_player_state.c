#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "town/player/scene_action_setup.h"
#include "town/player.h"
#include "town/player/state.h"

/* Advances and refreshes the state, then processes it when its increment is nonnegative. */
void advance_player_state(struct TownObjectRecord *context, EntityRec *state, SpriteFrameState *updateData) {
    state->z.v = (s32) (state->z.v + state->flags14);
    add_vertical_gravity(state);
    if (state->flags14 >= 0) {
        initialize_player_linked_record(context, state, updateData);
    }
}
