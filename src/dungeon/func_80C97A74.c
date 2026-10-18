#include "modules/dungeon_ovl_cb3000.h"

void func_80175274(CB_80175274_CallbackState *state,void *position,void *sprite,void *entity) {
 if(propagate_actor_action_flag(state,position,sprite,entity) != 0)
  state->handler=func_8017102C;
}
