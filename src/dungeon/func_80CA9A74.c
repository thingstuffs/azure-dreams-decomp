#include "modules/dungeon_ovl_cc5000.h"

void func_80163274(CL_CC5000_80175274_CallbackState *state,void *position,void *sprite,void *entity) {
 if(propagate_actor_action_flag(state,position,sprite,entity) != 0)
  state->handler=func_8015F02C;
}
