#include "common.h"
#include "m2c_compat.h"

/* extern */

typedef struct S_800C81E4_0 {
    u8 pad_00[0x6C];
    s16 unk_6C;
} S_800C81E4_0;   /* arg0 in func_800C81E4 */

typedef struct S_800C81E4_1 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_800C81E4_1;   /* arg1 in func_800C81E4 */


M2C_UNK func_800C8194(S_800C81E4_0 *, S_800C81E4_1 *);
/* Update the output, adding eight while the state's countdown is positive. */
void func_800C81E4(S_800C81E4_0 *state, S_800C81E4_1 *output) {
    func_800C8194(state, output);
    if (state->unk_6C > 0) {
        output->unk_06 = (u16) (output->unk_06 + 8);
        state->unk_6C = (s16) ((u16) state->unk_6C - 1);
    }
}
