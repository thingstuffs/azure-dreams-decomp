#include "modules/dungeon_ovl_e0365c.h"

void func_8017246C(E_8017246C_ActionState *state,void *motion,void *sprite,void *actor) {
 if(dungeonUpdateActorMovementToTile(state,motion,sprite,actor)!=0) {
  dungeonReduceActorFoodMeter(actor,4);
  dungeonAdvanceStatusTimers(actor);
  if((dungeonCheckActorFloorTrap(sprite,actor)<<16)>0) {
   state->handler=func_80170E5C;
   state->timer=0;
  }
 }
}
