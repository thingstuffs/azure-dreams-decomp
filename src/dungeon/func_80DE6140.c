#include "modules/dungeon_ovl_e0365c.h"

void func_80173940(E_80173940_ActionState *state,void *motion,void *sprite,void *actor) {
 if(dungeonUpdateSpinningActorFall(state,motion,sprite,actor) != 0) state->handler=func_80170E5C;
}
