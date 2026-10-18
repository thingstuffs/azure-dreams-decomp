/* Relink of matched dungeon/func_80DE61E8; every changed retail word is a paired relocation. */
#include "modules/dungeon_ovl_e0365c.h"
extern void func_8014CE5C(void *, void *, void *, void *);

void func_8014F9E8(E_801739E8_ActionState *state,void *motion,void *sprite,void *actor) {
 if(propagate_actor_action_flag(state,motion,sprite,actor) != 0) state->handler=func_8014CE5C;
}
