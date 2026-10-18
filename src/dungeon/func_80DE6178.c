#include "modules/dungeon_ovl_e0365c.h"

void func_80173978(E_80173978_ActionState *state,void *motion,void *sprite,void *actor) {
 if(update_actor_fade_in(state,motion,sprite,actor) != 0) state->handler=update_actor_behavior_facing_and_animation_2;
}
