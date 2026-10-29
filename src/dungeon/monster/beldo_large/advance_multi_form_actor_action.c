#include "common.h"
#include "m2c_compat.h"
#include "dungeon/monster/beldo_large.h"

extern void *beldo_actor_nodes[3];

typedef struct S_8016F2DC_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    s8 unk_9B;
} S_8016F2DC_0;

/* Clear two state fields and advance the byte counter. */
void advance_multi_form_actor_action(void) {
    S_8016F2DC_0 *state;

    state = beldo_actor_nodes[0] + 0x20;
    state->unk_9B = 0;
    state->unk_96 = 0;
    state->unk_9A = (u8) (state->unk_9A + 1);
}
