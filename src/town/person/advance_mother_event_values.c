#include "common.h"
#include "records/Rec_func_80094268_arg0.h"


#include "town/person/object_setup.h"
#include "town/person.h"
#include "town/person/object.h"


typedef struct S_800C7DB8_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800C7DB8_1;   /* arg1 in advance_mother_event_values */

/* Advances two values toward their targets and finalizes when the countdown expires. */
void advance_mother_event_values(Rec_func_80094268_arg0 *state, S_800C7DB8_1 *values, void *setup_context) {
    u16 steps_left;

    steps_left = state->unk_6C.as_u16 - 1;
    state->unk_6C.as_u16 = steps_left;
    if ((s16) steps_left <= 0) {
        apply_object_setup_and_update(state, values, setup_context);
        values->unk_02 = (u16) state->unk_84.as_u16;
        values->unk_06 = (s16) state->unk_86.as_u16;
        return;
    }
    values->unk_02 = (u16) (values->unk_02 + ((s32) ((s16) state->unk_84.as_u16
        - (s16) values->unk_02) / (s16) steps_left));
    values->unk_06 = (s16) ((u16) values->unk_06 + ((s32) ((s16) state->unk_86.as_u16
        - values->unk_06) / (s16) state->unk_6C.as_u16));
}
