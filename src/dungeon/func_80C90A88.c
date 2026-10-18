/* Relink of matched dungeon/func_80C97A74; every changed retail word is a paired relocation. */
#include "modules/dungeon_ovl_cb3000.h"
extern void func_8014D650(void *, void *, void *, void *);

void func_80150288(CB_80175274_CallbackState *state,void *position,void *sprite,void *entity) {
 if(propagate_actor_action_flag(state,position,sprite,entity) != 0)
  state->handler=func_8014D650;
}
