#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CCF60_0 {
    u8 pad_00[0x68];
    u16 unk_68;
    u8 pad_6A[0x8];
    s16 unk_72;
} S_800CCF60_0;   /* arg0 in func_800CCF60 */

/* Clear the value at 0x72 and increment the counter at 0x68. */
void func_800CCF60(S_800CCF60_0 *state) {
    state->unk_72 = 0;
    state->unk_68 = (u16) (state->unk_68 + 1);
}
