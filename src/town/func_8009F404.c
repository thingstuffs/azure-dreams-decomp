#include "common.h"

extern s32 D_800D0678[];
extern void townSelectObjectStateByMode(s32, s32, s32, s32, s32, s32 *);

/* Initialize the actor's action with shared state data and D_800D0678. */
void townInitializeActorActionWithDefaults(s32 actor, s32 action_id, s32 action_state, s32 state_data) {
    townSelectObjectStateByMode(actor, action_id, action_state, state_data, state_data, D_800D0678);
}
