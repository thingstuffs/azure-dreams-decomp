/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "town/player/scene_action_setup.h"

extern void initialize_actor_action_with_defaults(void *actor, void *action_id, void *action_state, void *state_data);
extern s32 D_800F8FD8[];

void initialize_flagged_actor_action_c(void *actor, void *action_id, void *action_state) {
    initialize_actor_action_with_defaults(actor, action_id, action_state, &D_800F8FD8[0]);
    *(s16 *)((u8 *)action_state + 0x10) = 0;
    *(u16 *)((u8 *)action_state + 0x14) = *(u16 *)((u8 *)action_state + 0x14) | 0x1C;
}
