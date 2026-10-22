#include "engine/message/callbacks.h"
#include "engine/message/state.h"

typedef struct S_80038464_0 {
    u8 pad_00[0x10];
    MessageFlagHandler message_handler; /* 0x10 */
    u8 pad_14[0x70];
    s8 advance_requested; /* 0x84 */
} S_80038464_0;   /* arg0 in clear_runtime_state_and_set_handler */




/* Clear the object's state byte and set its handler to advance_message_on_flag. */
void clear_runtime_state_and_set_handler(S_80038464_0 *object) {
    object->advance_requested = 0;
    object->message_handler = &advance_message_on_flag;
}
