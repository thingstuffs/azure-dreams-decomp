
#include "common.h"
#include "dungeon/actor/motion.h"
#include "dungeon/monster/hikewne.h"

/* extern */

typedef struct S_80173588_0 {
    u8 pad_00[0xA2];
    s16 unk_A2;
} S_80173588_0;   /* arg0 in reset_state_field_a_2 */



/* Call update_actor_hop_and_shrink and clear the state field at offset 0xA2. */
void reset_state_field_a_2(S_80173588_0 *state, void *context, SpriteFrameState *data, void *render) {
    update_actor_hop_and_shrink(state, context, data, render);
    state->unk_A2 = 0;
}
