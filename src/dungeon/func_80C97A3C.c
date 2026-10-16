#include "modules/dungeon_ovl_cb3000.h"

void func_8017523C(CB_8017523C_CallbackState *state,void *position,void *sprite,void *entity) {
 if(dungeonResolveActorFloorTrapOnce(state,position,sprite,entity) > 0)
  state->handler=func_8017102C;
}
