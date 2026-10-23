#include "common.h"
#include "m2c_compat.h"

extern s32 ghosh_actor_node;

typedef struct S_8016DECC_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x3];
    s8 unk_9B;
} S_8016DECC_0;

/* Clears the two action fields at offsets 0x9B and 0x96 in the Ghosh actor data. */
void reset_active_encounter_action_state(void) {
    S_8016DECC_0 *state;

    state = ghosh_actor_node + 0x20;
    state->unk_9B = 0;
    state->unk_96 = 0;
}
