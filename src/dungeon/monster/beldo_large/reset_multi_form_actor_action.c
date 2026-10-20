#include "common.h"
#include "m2c_compat.h"

extern s32 D_80175D50;

typedef struct S_8016F2BC_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_8016F2BC_0;

/* Clears three state fields in the current object. */
void reset_multi_form_actor_action(void) {
    S_8016F2BC_0 *state;

    state = D_80175D50 + 0x20;
    state->unk_9A = 0;
    state->unk_9B = 0;
    state->unk_96 = 0;
}
