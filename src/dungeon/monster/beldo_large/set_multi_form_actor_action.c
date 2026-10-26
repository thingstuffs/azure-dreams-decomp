#include "common.h"
#include "m2c_compat.h"

extern void *beldo_actor_nodes[3];

typedef struct S_8016F304_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_8016F304_0;

/* Sets the state ID and clears the associated byte and halfword. */
void set_multi_form_actor_action(s8 state_id) {
    S_8016F304_0 *state;

    state = beldo_actor_nodes[0] + 0x20;
    state->unk_9A = state_id;
    state->unk_9B = 0;
    state->unk_96 = 0;
}
