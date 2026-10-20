#include "common.h"
#include "m2c_compat.h"

void initialize_actor_action_with_defaults(s32, s32, s32, s32);                   /* extern */
extern M2C_UNK D_800F8A4C;

/* Initialize the object's action state using D_800F8A4C. */
void initialize_object_action_with_default_data(s32 object, s32 action, s32 state) {
    initialize_actor_action_with_defaults(object, action, state, (s32)(&D_800F8A4C));
}
