#include "common.h"
#include "records/Rec_func_80094268_arg0.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_800C4174();



typedef struct S_800C7DB8_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800C7DB8_1;   /* arg1 in func_800C7DB8 */

/* Advances two values toward their targets and finalizes when the countdown expires. */
void func_800C7DB8(Rec_func_80094268_arg0 *state, S_800C7DB8_1 *values) {
    u16 steps_left;

    steps_left = state->unk_6C.as_u16 - 1;
    state->unk_6C.as_u16 = steps_left;
    if ((s16) steps_left <= 0) {
        func_800C4174(state);
        values->unk_02 = (u16) state->unk_84.as_u16;
        values->unk_06 = (s16) state->unk_86.as_u16;
        return;
    }
    values->unk_02 = (u16) (values->unk_02 + ((s32) ((s16) state->unk_84.as_u16 - (s16) values->unk_02) / (s16) steps_left));
    values->unk_06 = (s16) ((u16) values->unk_06 + ((s32) ((s16) state->unk_86.as_u16 - values->unk_06) / (s16) state->unk_6C.as_u16));
}
