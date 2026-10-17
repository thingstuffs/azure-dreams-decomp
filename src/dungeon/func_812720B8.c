/* Relink of matched dungeon/func_8132644C; every changed retail word is a paired relocation. */
#define func_8016B778 func_80153514
/* Relink of matched dungeon/func_80DE61E8; every changed retail word is a paired relocation. */
#define func_80170E5C func_80153514
#include "modules/dungeon_ovl_e0365c.h"

void func_801558B8(E_801739E8_ActionState *state,void *motion,void *sprite,void *actor) {
 if(dungeonPropagateActorActionFlag(state,motion,sprite,actor) != 0) state->handler=func_80153514;
}
