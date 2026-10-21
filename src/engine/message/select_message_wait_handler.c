#include "common.h"

#include "common.h"
#include "records/Rec_func_800381D0_arg0.h"
#include "engine/message.h"
#include "slus.h"

/* Selects the next handler based on runtime status and the context byte. */
s32 *select_message_wait_handler(Rec_func_800381D0_arg0 *context) {
    if (read_sound_mode_blocking_status(4) != 0x100) {
        if (play_message_confirmation_sound(*context->unk_1C) != 0) {
            return &finish_message_when_idle;
        }
        return &consume_message_byte_and_start_countdown;
    }
    return &choose_message_wait_handler;
}
