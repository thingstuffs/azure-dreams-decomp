/* Relink of matched dungeon/func_80E3A154; every changed retail word is a paired relocation. */
#define func_80170E5C func_8016500C
/* Relink of matched dungeon/func_80DE61E8; every changed retail word is a paired relocation. */
#define func_8016500C func_80165094
#include "modules/dungeon_ovl_e0365c.h"
extern void func_80165094(void *, void *, void *, void *);

void func_8016872C(E_801739E8_ActionState *state,void *motion,void *sprite,void *actor) {
 if(dungeonPropagateActorActionFlag(state,motion,sprite,actor) != 0) state->handler=func_80165094;
}
