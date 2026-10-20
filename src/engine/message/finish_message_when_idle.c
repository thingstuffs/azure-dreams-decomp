#include "common.h"

#include "common.h"
typedef struct S_8003832C_0 S_8003832C_0;
void consume_message_byte_and_start_countdown(S_8003832C_0 *context);                         /* extern */
s32 func_80053EF0();                         /* extern */

/* Call the handler when check 4 returns zero. */
void finish_message_when_idle(s32 handler_arg) {
    if (func_80053EF0(4) == 0) {
        consume_message_byte_and_start_countdown(handler_arg);
    }
}
