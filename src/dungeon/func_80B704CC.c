/* Relink of matched dungeon/func_80B48214; every changed retail word is a paired relocation. */
#include "modules/dungeon_resource12_slot0.h"
extern void update_actor_behavior_facing_and_animation_2(void *, void *, void *, void *);

void func_80173CCC(Resource12CallbackState *state, void *motion, void *position, void *actor)
{
    if (propagate_actor_action_flag(state, motion, position, actor) > 0) {
        state->callback = update_actor_behavior_facing_and_animation_2;
    }
}
