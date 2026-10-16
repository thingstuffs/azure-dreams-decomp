#include "modules/dungeon_ovl_cb9000.h"

void func_8016F23C(CL_CB9000_8017523C_CallbackState *state,void *position,void *sprite,void *entity) {
 if(func_800AB464(state,position,sprite,entity) > 0)
  state->handler=func_8016B02C;
}
