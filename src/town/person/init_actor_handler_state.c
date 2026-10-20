#include "common.h"
#include "shared/object_index_slots.h"

extern s32 D_800C5100;

typedef struct S_800C51DC_0 {
    u8 pad_00[0x54];
    s32 * unk_54;
    u8 pad_58[0x8];
    s32 unk_60;
} S_800C51DC_0;   /* arg0 in init_actor_handler_state */

typedef struct S_800C51DC_1 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
} S_800C51DC_1;   /* arg1 in init_actor_handler_state */

/* Clear the actor table flag, install its handler, and initialize state values. */
void init_actor_handler_state(S_800C51DC_0 *actor, S_800C51DC_1 *state) {
    D_80082660[actor->unk_60].unk_00 = 0;
    actor->unk_54 = &D_800C5100;
    state->unk_10 = 0x80000;
    state->unk_14 = 0x40000;
}
