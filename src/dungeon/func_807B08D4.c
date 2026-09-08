#include "common.h"
#include "m2c_compat.h"

extern s32 D_800FBE1C;

typedef struct S_807B08D4_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x3];
    s8 unk_9B;
} S_807B08D4_0;   /* temp_v0 in func_807B08D4 */

/* Clears the state block's fields at offsets 0x96 and 0x9B. */
void func_807B08D4(void) {
    S_807B08D4_0 *state;

    state = D_800FBE1C + 0x20;
    state->unk_96 = 0;
    state->unk_9B = 0;
}
