#include "modules/dungeon_ovl_cd7000.h"

void func_80151274(CL_CD7000_80175274_CallbackState *state,void *position,void *sprite,void *entity) {
 if(dungeonPropagateActorActionFlag(state,position,sprite,entity) != 0)
  state->handler=func_8014D02C;
}
