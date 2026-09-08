#include "common.h"
#include "m2c_compat.h"

typedef struct S_8016F140_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_8016F140_0;   /* arg0 in func_8016F140 */

/* Clear the state byte and the high bits of the two flag fields. */
void func_8016F140(S_8016F140_0 *state) {
    state->unk_6D = 0;
    state->unk_71 = (u8) (state->unk_71 & 0x7F);
    state->unk_46 = (u16) (state->unk_46 & 0x7FFF);
}
