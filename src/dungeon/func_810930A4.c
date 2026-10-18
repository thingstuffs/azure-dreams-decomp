/* Relink of matched dungeon/func_80E3A154; every changed retail word is a paired relocation. */
#define update_actor_behavior_facing_and_animation_2 func_80164E0C
/* Relink of matched dungeon/func_80DE61E8; every changed retail word is a paired relocation. */
#define func_80164E0C func_80164E94
#include "modules/dungeon_ovl_e0365c.h"
extern void func_80164E94(void *, void *, void *, void *);

void func_801688A4(E_801739E8_ActionState *state,void *motion,void *sprite,void *actor) {
 if(propagate_actor_action_flag(state,motion,sprite,actor) != 0) state->handler=func_80164E94;
}
