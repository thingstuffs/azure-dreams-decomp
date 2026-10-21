#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "records/Rec_func_800384A8_arg0.h"
#include "engine/message.h"
#include "slus.h"

/* Sets the next handler on status 0x100; otherwise runs the fallback handler. */
void wait_message_voice_busy(Rec_func_800384A8_arg0 *state) {
    if (func_80053EF0(4) != 0x100) {
        play_message_advance_sound(state);
        return;
    }
    state->unk_10 = &wait_message_voice_idle;
}
