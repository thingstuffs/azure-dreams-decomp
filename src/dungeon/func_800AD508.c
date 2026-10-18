#include "common.h"
#include "m2c_compat.h"

/* extern */
extern M2C_UNK D_800B2A60;

typedef struct S_800B2C68_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
} S_800B2C68_0;   /* arg0 in set_effect_state_pointer_on_success */


s32 update_linked_actor_motion(S_800B2C68_0 *, void *, void *, void *);
/* Set the state pointer to D_800B2A60 when update_linked_actor_motion succeeds. */
void set_effect_state_pointer_on_success(S_800B2C68_0 *state, void *context, void *data, void *extra_data) {
    if (update_linked_actor_motion(state, context, data, extra_data) != 0) {
        state->unk_8C = &D_800B2A60;
    }
}
