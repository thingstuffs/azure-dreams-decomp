#include "modules/dungeon_ovl_e0365c.h"

void func_80173908(E_80173908_ActionState *state,void *motion,void *sprite,void *actor) {
 if(interpolate_actor_to_terrain_tile(state,motion,sprite,actor) != 0) state->handler=update_actor_behavior_facing_and_animation_2;
}
