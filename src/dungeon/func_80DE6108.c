#include "modules/dungeon_ovl_e0365c.h"

void func_80173908(E_80173908_ActionState *state,void *motion,void *sprite,void *actor) {
 if(dungeonInterpolateActorToTerrainTile(state,motion,sprite,actor) != 0) state->handler=func_80170E5C;
}
