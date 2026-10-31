#include "common.h"
#include "dungeon/effect.h"
#include "dungeon/actor/motion.h"

/* extern */

typedef struct S_800B2C68_0 {
    u8 pad_00[0x8C];
    void (*unk_8C)(u8 *, s32,  u8 *, u8 *);
} S_800B2C68_0;   /* arg0 in set_effect_state_pointer_on_success */

/* Set the state pointer to dispatch_target_action when update_linked_actor_motion succeeds. */
void set_effect_state_pointer_on_success(S_800B2C68_0 *state, ObjectPosition *context, SpriteFrameState *data, ActorRecord *extra_data) {
    if (update_linked_actor_motion(state, context, data, extra_data) != 0) {
        state->unk_8C = &dispatch_target_action;
    }
}
