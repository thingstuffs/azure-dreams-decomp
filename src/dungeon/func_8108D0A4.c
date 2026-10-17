/* Relink of matched dungeon/func_80E3A154; every changed retail word is a paired relocation. */
#define func_80170E5C func_8016AE0C
/* Relink of matched dungeon/func_80DE61E8; every changed retail word is a paired relocation. */
#define func_8016AE0C func_8016AE94
#include "modules/dungeon_ovl_e0365c.h"
extern void func_8016AE94(void *, void *, void *, void *);

void func_8016E8A4(E_801739E8_ActionState *state,void *motion,void *sprite,void *actor) {
 if(dungeonPropagateActorActionFlag(state,motion,sprite,actor) != 0) state->handler=func_8016AE94;
}
