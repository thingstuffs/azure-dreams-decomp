#include "modules/dungeon_ovl_ccb000.h"

void func_8015D23C(CL_CCB000_8017523C_CallbackState *state,void *position,void *sprite,void *entity) {
 if(func_800AB464(state,position,sprite,entity) > 0)
  state->handler=func_8015902C;
}
