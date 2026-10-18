#include "modules/dungeon_ovl_e0365c.h"

void func_801739B0(E_801739B0_ActionState *state,void *motion,void *sprite,void *actor) {
 if(resolve_actor_floor_trap_once(state,motion,sprite,actor) > 0) state->handler=update_actor_behavior_facing_and_animation_2;
}
