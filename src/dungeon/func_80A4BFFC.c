#include "modules/dungeon_resource06_slot0.h"

void func_801757FC(Resource06CallbackState *state, void *motion, void *position, void *actor)
{
    if (resolve_actor_floor_trap_once(state, motion, position, actor) > 0) {
        state->callback = initialize_destination_state;
    }
}
