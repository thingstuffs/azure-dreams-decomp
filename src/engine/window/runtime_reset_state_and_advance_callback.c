#include "common.h"

#include "common.h"
#include "slus/data.h"

typedef struct S_80035760_0 {
    u8 pad_00[0x4C];
    u8 unk_4C;
    u8 unk_4D;
    u8 pad_4E[0x3];
    u8 unk_51;
    u8 pad_52[0x16];
    s32 * unk_68;
    u8 pad_6C[0x8];
    u8 * unk_74;
} S_80035760_0;   /* arg0 in runtime_reset_state_and_advance_callback */

/* Reset the state bytes and advance the callback when the shared flag or state requests it. */
void runtime_reset_state_and_advance_callback(S_80035760_0 *state) {
    u8 *shared_flag;

    shared_flag = state->unk_74;
    if ((*shared_flag == 1) || (state->unk_51 == 0xFF)) {
        *shared_flag = 1;
        state->unk_4C = 0xFE;
        state->unk_4D = 0xFE;
        state->unk_51 = 0U;
        state->unk_68 = &runtime_assign_code_101_callback;
    }
}
