#include "common.h"
#include "dungeon/monster/ghosh.h"
#include "m2c_compat.h"


typedef struct S_8016DECC_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x3];
    s8 unk_9B;
} S_8016DECC_0;

/* Clears the two action fields at offsets 0x9B and 0x96 in the Ghosh actor data. */
void reset_active_encounter_action_state(void) {
    ActorRecord *state;
    void *body;

    body = ghosh_actor_node + 1;
    state = body;
    state->action_phase.s = 0;
    state->action_timer.s = 0;
}
