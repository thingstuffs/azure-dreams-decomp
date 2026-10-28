#include "common.h"

#include "common.h"
#include "engine/message.h"
#include "engine/script.h"
#include "slus.h"
#include "engine/message/state.h"




/* Opcode 0x06: Voice wait: when gated, rewind while the sound status is nonzero; otherwise hand over to advance_message_when_voice_idle once the status is 0x100, else send SD_Call(0xB4). */
void script_wait_voice_then_advance(MessageVoiceState *state) {
    s32 status;

    status = read_sound_mode_blocking_status(4);
    if (check_state_or_global_flags(state) != 0) {
        if (status != 0) {
            state->action = 0;
            state->cursor = state->cursor - 1;
        }
    } else {
        if (status == 0x100) {
            state->action = &advance_message_when_voice_idle;
            return;
        }
        SD_Call(0xB4);
    }
}
