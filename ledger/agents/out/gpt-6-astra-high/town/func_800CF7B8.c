#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CCF18_0 {
    u8 pad_00[0x68];
    u16 unk_68;
    u8 pad_6A[0x8];
    s16 unk_72;
} S_800CCF18_0;   /* arg0 in func_800CCF18 */

/* Sets unk_72 to 0xC00 and increments the unk_68 counter. */
void func_800CCF18(S_800CCF18_0 *state) {
    state->unk_72 = 0xC00;
    state->unk_68 = (u16) (state->unk_68 + 1);
}
