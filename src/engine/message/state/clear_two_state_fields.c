#include "common.h"

#include "common.h"
#include "engine/message/state.h"
#include "engine/message/callbacks.h"

typedef struct S_80038570_0 {
    u8 pad_00[0x10];
    MessageConfirmHandler message_handler; /* 0x10 */
    u8 pad_14[0x13];
    s8 unk_27;
    u8 pad_28[0x5C];
    s8 advance_requested; /* 0x84 */
} S_80038570_0;   /* arg0 in clear_two_state_fields */




/* Clear two state fields and set the next handler. */
void clear_two_state_fields(S_80038570_0 *state) {
    state->unk_27 = 0;
    state->advance_requested = 0;
    state->message_handler = &advance_message_on_confirm_flag;
}
