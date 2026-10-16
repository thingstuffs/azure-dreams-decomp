#include "modules/dungeon_ovl_cb9000.h"

void func_8016F274(CL_CB9000_80175274_CallbackState *state,void *position,void *sprite,void *entity) {
 if(func_800AC7EC(state,position,sprite,entity) != 0)
  state->handler=func_8016B02C;
}
