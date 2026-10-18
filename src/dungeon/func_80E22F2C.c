/* Relink of matched dungeon/func_80E3A154; every changed retail word is a paired relocation. */
#define update_actor_behavior_facing_and_animation_2 func_8015F00C
/* Relink of matched dungeon/func_80DE61E8; every changed retail word is a paired relocation. */
#define func_8015F00C func_8015F094
#include "modules/dungeon_ovl_e0365c.h"
extern void func_8015F094(void *, void *, void *, void *);

void func_8016272C(E_801739E8_ActionState *state,void *motion,void *sprite,void *actor) {
 if(propagate_actor_action_flag(state,motion,sprite,actor) != 0) state->handler=func_8015F094;
}
