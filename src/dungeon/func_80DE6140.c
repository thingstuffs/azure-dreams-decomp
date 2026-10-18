#include "modules/dungeon_ovl_e0365c.h"

void func_80173940(E_80173940_ActionState *state,void *motion,void *sprite,void *actor) {
 if(update_spinning_actor_fall(state,motion,sprite,actor) != 0) state->handler=update_actor_behavior_facing_and_animation_2;
}
