#include "modules/dungeon_ovl_cd7000.h"

void func_8015123C(CL_CD7000_8017523C_CallbackState *state,void *position,void *sprite,void *entity) {
 if(dungeonResolveActorFloorTrapOnce(state,position,sprite,entity) > 0)
  state->handler=func_8014D02C;
}
