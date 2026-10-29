#include "common.h"
#include "dungeon/actor.h"

/* Forward all four effect callback arguments and the result. */
s32 forward_actor_defeat_removal_second(u8 *state, s32 *position, u8 *sprite, u8 *entity_data) {
    return update_actor_defeat_removal(state, position, sprite, entity_data);
}
