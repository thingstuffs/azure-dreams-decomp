#include "modules/dungeon_ovl_e0365c.h"

void func_801737DC(E_801737DC_ActionState *state,void *motion,E_801737DC_RenderState *sprite,E_801737DC_RenderActor *actor) {
 if(func_800AC82C(state,motion,sprite,actor)!=0) {
  if((func_800AD9B4(sprite,actor)<<16)>0) state->handler=func_80170E5C;
 } else if(sprite->frames==D_80174538 && !(actor->flags&0x208)) {
  sprite->frames=D_80174518;
  func_80047784(sprite,D_80174518[((gameWork.view.viewAngle+actor->facing+0x100)>>9)&7],0);
 }
}
