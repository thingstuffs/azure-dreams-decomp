#include "modules/dungeon_ovl_e0365c.h"

void func_8017321C(E_8017321C_ActionState *state,void *motion,void *sprite,void *actor) {
 if(update_actor_hop_and_grow(state,motion,sprite,actor) != 0) state->handler=update_actor_behavior_facing_and_animation_2;
}
