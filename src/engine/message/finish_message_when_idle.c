#include "common.h"

#include "common.h"
#include "engine/message.h"
#include "slus.h"
typedef struct S_8003832C_0 S_8003832C_0;

/* Call the handler when check 4 returns zero. */
void finish_message_when_idle(s32 handler_arg) {
    if (func_80053EF0(4) == 0) {
        consume_message_byte_and_start_countdown(handler_arg);
    }
}
