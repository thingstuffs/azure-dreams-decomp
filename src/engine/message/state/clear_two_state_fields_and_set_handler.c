#include "common.h"

#include "common.h"

typedef struct S_80038630_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0x13];
    s8 unk_27;
    u8 pad_28[0x5C];
    s8 unk_84;
} S_80038630_0;   /* arg0 in clear_two_state_fields_and_set_handler */


extern s32 advance_message_on_ready_flag;

/* Clears two state fields and sets the next handler to advance_message_on_ready_flag. */
void clear_two_state_fields_and_set_handler(S_80038630_0 *state) {
    state->unk_27 = 0;
    state->unk_84 = 0;
    state->unk_10 = &advance_message_on_ready_flag;
}
