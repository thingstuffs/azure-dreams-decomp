#include "modules/dungeon_ovl_e0365c.h"

void update_thrown_actor_and_trap(E_801738A4_ActionState *state,void *motion,void *sprite,void *actor) {
 if(update_thrown_actor_travel(state,motion,sprite,actor)!=0 &&
    (check_actor_floor_trap(sprite,actor)<<16)>0) state->handler=update_actor_behavior_facing_and_animation_2;
}
