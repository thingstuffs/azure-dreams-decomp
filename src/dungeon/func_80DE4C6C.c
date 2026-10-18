#include "modules/dungeon_ovl_e0365c.h"

void move_actor_to_tile_and_check_trap(E_8017246C_ActionState *state,void *motion,void *sprite,void *actor) {
 if(update_actor_movement_to_tile(state,motion,sprite,actor)!=0) {
  reduce_actor_food_meter(actor,4);
  advance_status_timers(actor);
  if((check_actor_floor_trap(sprite,actor)<<16)>0) {
   state->handler=update_actor_behavior_facing_and_animation_2;
   state->timer=0;
  }
 }
}
