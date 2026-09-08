#include "common.h"
#include "m2c_compat.h"

/* extern */

typedef struct S_80125420_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    s16 unk_06;
    u8 pad_08[0x2];
    s8 unk_0A;
} S_80125420_0;   /* arg0 in func_80125420 */


M2C_UNK func_801248C0(S_80125420_0 *);
/* Advance the counter and invoke completion when it reaches the target, then reset the state. */
void func_80125420(S_80125420_0 *state) {
    u16 next_count;

    next_count = state->unk_04 + 1;
    state->unk_04 = next_count;
    if ((s16) next_count == state->unk_06) {
        func_801248C0(state);
        state->unk_0A = 8;
        state->unk_06 = 0;
        state->unk_04 = 0U;
    }
}
