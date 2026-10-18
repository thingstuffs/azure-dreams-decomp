#include "modules/dungeon_ovl_e0365c.h"

void func_801739E8(E_801739E8_ActionState *state,void *motion,void *sprite,void *actor) {
 if(propagate_actor_action_flag(state,motion,sprite,actor) != 0) state->handler=update_actor_behavior_facing_and_animation_2;
}
