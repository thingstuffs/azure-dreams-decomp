#include "modules/dungeon_ovl_ccb000.h"

void func_8015D274(CL_CCB000_80175274_CallbackState *state,void *position,void *sprite,void *entity) {
 if(dungeonPropagateActorActionFlag(state,position,sprite,entity) != 0)
  state->handler=func_8015902C;
}
