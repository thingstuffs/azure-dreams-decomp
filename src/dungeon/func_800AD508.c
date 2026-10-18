#include "common.h"
/* extern */
void dispatch_target_action(u8 *actor, s32 action_context, u8 *destination, u8 *target);

typedef struct S_800B2C68_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
} S_800B2C68_0;   /* arg0 in set_effect_state_pointer_on_success */


s32 update_linked_actor_motion(S_800B2C68_0 *, void *, void *, void *);
/* Set the state pointer to dispatch_target_action when update_linked_actor_motion succeeds. */
void set_effect_state_pointer_on_success(S_800B2C68_0 *state, void *context, void *data, void *extra_data) {
    if (update_linked_actor_motion(state, context, data, extra_data) != 0) {
        state->unk_8C = &dispatch_target_action;
    }
}
