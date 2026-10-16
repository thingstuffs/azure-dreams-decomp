#include "modules/dungeon_ovl_e0365c.h"

void func_8017246C(E_8017246C_ActionState *state,void *motion,void *sprite,void *actor) {
 if(func_800AB1C0(state,motion,sprite,actor)!=0) {
  func_800AD594(actor,4);
  func_800A4ACC(actor);
  if((func_800AD9B4(sprite,actor)<<16)>0) {
   state->handler=func_80170E5C;
   state->timer=0;
  }
 }
}
