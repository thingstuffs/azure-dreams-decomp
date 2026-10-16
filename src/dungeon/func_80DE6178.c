#include "modules/dungeon_ovl_e0365c.h"

void func_80173978(E_80173978_ActionState *state,void *motion,void *sprite,void *actor) {
 if(dungeonUpdateActorFadeIn(state,motion,sprite,actor) != 0) state->handler=func_80170E5C;
}
