#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009CB64();                   /* extern */
extern M2C_UNK D_800F8A58;

/* Initialize the actor's action using D_800F8A58. */
void func_8009CBB4(s32 actor, s32 action_id, s32 action_state) {
    func_8009CB64(actor, action_id, action_state, &D_800F8A58);
}
