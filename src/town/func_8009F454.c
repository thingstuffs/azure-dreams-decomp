#include "common.h"
#include "m2c_compat.h"

void townInitializeActorActionWithDefaults();                   /* extern */
extern M2C_UNK D_800F8A58;

/* Initialize the actor's action using D_800F8A58. */
void townInitializeActorActionWithDefaultData(s32 actor, s32 action_id, s32 action_state) {
    townInitializeActorActionWithDefaults(actor, action_id, action_state, &D_800F8A58);
}
