#include "common.h"
#include "dungeon/monster/ghosh.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_80170CA0_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
} S_80170CA0_0;

/* Clear the current object's two state fields. */
void clear_the_s_two_state_fields(void) {
    ActorRecord *state;
    void *body;

    body = ghosh_scripted_actor + 1;
    state = body;
    state->action_id.s = 0;
    state->action_timer.s = 0;
}
