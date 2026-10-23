#include "shared/audio_commands.h"
#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "records/Rec_func_800384A8_arg0.h"
#include "slus.h"
#include "slus/data.h"

/* Calls SD_Call with 0xB4 and installs update_message_window as the next handler. */
void play_message_advance_sound(Rec_func_800384A8_arg0 *state) {
    SD_Call(AUDIO_FADE_CD_FAST);
    state->unk_10 = &update_message_window;
}
