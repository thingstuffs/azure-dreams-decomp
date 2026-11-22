#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "town/player/scene_action_setup.h"
#include "town/player.h"
#include "town/player/state.h"

/* Advances and refreshes the state, then processes it when its increment is nonnegative. */
void advance_player_state(struct TownObjectRecord *context, ObjectPosition *position, SpriteFrameState *updateData) {
    position->z.v += position->velocity_z;
    add_vertical_gravity(position);
    if (position->velocity_z >= 0) {
        initialize_player_linked_record(context, position, updateData);
    }
}
