#include "modules/dungeon_ovl_e0365c.h"

void update_actor_landing_and_trap(E_801737DC_ActionState *state,void *motion,E_801737DC_RenderState *sprite,E_801737DC_RenderActor *actor) {
 if(update_actor_transform_from_parent(state,motion,sprite,actor)!=0) {
  if((check_actor_floor_trap(sprite,actor)<<16)>0) state->handler=update_actor_behavior_facing_and_animation_2;
 } else if(sprite->frames==D_80174538 && !(actor->flags&0x208)) {
  sprite->frames=D_80174518;
  func_80047784(sprite,D_80174518[((g_game_work.view.viewAngle+actor->facing+0x100)>>9)&7],0);
 }
}
