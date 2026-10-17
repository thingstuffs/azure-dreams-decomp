/* Relink of matched dungeon/func_80E3A154; every changed retail word is a paired relocation. */
#define func_80170E5C func_80170E0C
#define func_80170EE4 func_80170E94
/* Relink of matched dungeon/func_80DE61E8; every changed retail word is a paired relocation. */
#define func_80170E0C func_80170E94
#include "modules/dungeon_ovl_e0365c.h"

void func_801748A4(E_801739E8_ActionState *state,void *motion,void *sprite,void *actor) {
 if(dungeonPropagateActorActionFlag(state,motion,sprite,actor) != 0) state->handler=func_80170E94;
}
