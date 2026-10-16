#include "modules/dungeon_ovl_e0365c.h"

void func_80172850(E_80172850_ActionState *state,void *motion,void *sprite,void *actor) {
 if(func_800AB378(state,motion,sprite,actor)!=0 &&
    (func_800AD9B4(sprite,actor)<<16)>0) state->handler=func_80170E5C;
}
