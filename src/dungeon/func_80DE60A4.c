#include "modules/dungeon_ovl_e0365c.h"

void func_801738A4(E_801738A4_ActionState *state,void *motion,void *sprite,void *actor) {
 if(dungeonUpdateThrownActorTravel(state,motion,sprite,actor)!=0 &&
    (dungeonCheckActorFloorTrap(sprite,actor)<<16)>0) state->handler=func_80170E5C;
}
