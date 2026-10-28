#include "engine/message/callbacks.h"
#include "slus.h"
#include "engine/message.h"

typedef struct S_80038588_0 {
    u8 pad_00[0x10];
    MessageWindowHandler message_handler; /* 0x10 */
    u8 pad_14[0x70];
    s8 advance_requested; /* 0x84 */
} S_80038588_0;   /* arg0 in advance_message_on_confirm_flag */


/* Call SD_Call and update the object's handler when its flag is set. */
void advance_message_on_confirm_flag(S_80038588_0 *object) {
    if (object->advance_requested != 0) {
        SD_Call(0xB4);
        object->message_handler = &update_message_window;
    }
}
