#include "modules/dungeon_ovl_e0365c.h"

void func_8017321C(E_8017321C_ActionState *state,void *motion,void *sprite,void *actor) {
 if(dungeonUpdateActorHopAndGrow(state,motion,sprite,actor) != 0) state->handler=func_80170E5C;
}
