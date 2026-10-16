/* Relink of matched dungeon/func_80DE61E8; every changed retail word is a paired relocation. */
#define func_80170E5C func_8016F78C
#include "modules/dungeon_ovl_e0365c.h"

void func_80170A1C(E_801739E8_ActionState *state,void *motion,void *sprite,void *actor) {
 if(dungeonPropagateActorActionFlag(state,motion,sprite,actor) != 0) state->handler=func_8016F78C;
}
