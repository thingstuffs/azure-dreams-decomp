/* Relink of matched dungeon/func_8132644C; every changed retail word is a paired relocation. */
#define func_8016B778 update_actor_animation_and_dispatch_actions
/* Relink of matched dungeon/func_80DE61E8; every changed retail word is a paired relocation. */
#define update_actor_behavior_facing_and_animation_2 update_actor_animation_and_dispatch_actions
#include "modules/dungeon_ovl_e0365c.h"

void func_80151BF8(E_801739E8_ActionState *state,void *motion,void *sprite,void *actor) {
 if(propagate_actor_action_flag(state,motion,sprite,actor) != 0) state->handler=update_actor_animation_and_dispatch_actions;
}
