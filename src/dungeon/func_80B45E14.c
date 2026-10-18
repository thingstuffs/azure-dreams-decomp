#include "modules/dungeon_resource12_slot0.h"

void advance_familiar_defeat_sequence(void *state, void *motion, void *position, void *actor)
{
    update_actor_hop_and_shrink(state, motion, position, actor);
}
