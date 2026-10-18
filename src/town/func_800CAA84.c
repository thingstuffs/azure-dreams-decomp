#include "common.h"
#include "m2c_compat.h"

/* extern */

typedef struct S_800C81E4_0 {
    u8 pad_00[0x6C];
    s16 unk_6C;
} S_800C81E4_0;   /* arg0 in update_output_adding_eight_state */

typedef struct S_800C81E4_1 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_800C81E4_1;   /* arg1 in update_output_adding_eight_state */


void set_object_value_base_plus(S_800C81E4_0 *, S_800C81E4_1 *);
/* Update the output, adding eight while the state's countdown is positive. */
void update_output_adding_eight_state(S_800C81E4_0 *state, S_800C81E4_1 *output) {
    set_object_value_base_plus(state, output);
    if (state->unk_6C > 0) {
        output->unk_06 = (u16) (output->unk_06 + 8);
        state->unk_6C = (s16) ((u16) state->unk_6C - 1);
    }
}
