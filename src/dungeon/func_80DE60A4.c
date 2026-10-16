#include "modules/dungeon_ovl_e0365c.h"

void func_801738A4(E_801738A4_ActionState *state,void *motion,void *sprite,void *actor) {
 if(func_800AC010(state,motion,sprite,actor)!=0 &&
    (func_800AD9B4(sprite,actor)<<16)>0) state->handler=func_80170E5C;
}
