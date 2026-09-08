#include "common.h"
#include "m2c_compat.h"

extern s32 D_80175D64;

typedef struct S_80170510_0 {
    u8 pad_00[0x12];
    u16 unk_12;
    u8 pad_14[0x4];
    s16 unk_18;
} S_80170510_0;   /* temp_v1 in func_80170510 */

/* Clear the state value at 0x18 and increment the counter at 0x12. */
void func_80170510(void) {
    S_80170510_0 *state;

    state = D_80175D64 + 0x20;
    state->unk_18 = 0;
    state->unk_12 = (u16) (state->unk_12 + 1);
}
