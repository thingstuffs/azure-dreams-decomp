#include "common.h"
#include "m2c_compat.h"

/* extern */

typedef struct S_80173588_0 {
    u8 pad_00[0xA2];
    s16 unk_A2;
} S_80173588_0;   /* arg0 in reset_state_field_a_2 */


s32 update_actor_hop_and_shrink(S_80173588_0 *, void *, void *);
/* Call update_actor_hop_and_shrink and clear the state field at offset 0xA2. */
void reset_state_field_a_2(S_80173588_0 *state, void *context, void *data) {
    update_actor_hop_and_shrink(state, context, data);
    state->unk_A2 = 0;
}
