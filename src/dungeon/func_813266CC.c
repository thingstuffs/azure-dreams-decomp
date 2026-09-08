#include "common.h"
#include "m2c_compat.h"

extern s32 D_80174704;

typedef struct S_8016DECC_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x3];
    s8 unk_9B;
} S_8016DECC_0;   /* temp_v0 in func_8016DECC */

/* Clears two fields in the state block at D_80174704 + 0x20. */
void func_8016DECC(void) {
    S_8016DECC_0 *state;

    state = D_80174704 + 0x20;
    state->unk_9B = 0;
    state->unk_96 = 0;
}
