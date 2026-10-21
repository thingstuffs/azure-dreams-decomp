#include "common.h"

#include "common.h"

#include "records/Rec_func_800384A8_arg0.h"
#include "engine/message.h"
#include "slus.h"

/* Advance the object's callback once the channel 4 blocking status clears. */
void wait_message_voice_idle(s32 object) {
    if (read_sound_mode_blocking_status(4) != 0x100) {
        play_message_advance_sound(object);
    }
}
