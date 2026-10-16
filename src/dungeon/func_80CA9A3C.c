#include "modules/dungeon_ovl_cc5000.h"

void func_8016323C(CL_CC5000_8017523C_CallbackState *state,void *position,void *sprite,void *entity) {
 if(dungeonResolveActorFloorTrapOnce(state,position,sprite,entity) > 0)
  state->handler=func_8015F02C;
}
