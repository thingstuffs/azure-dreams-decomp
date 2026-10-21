#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "records/Rec_func_800384A8_arg0.h"
#include "slus.h"
#include "slus/data.h"

/* Calls SD_Call with 0xB4 and installs update_message_window as the next handler. */
void play_message_advance_sound(Rec_func_800384A8_arg0 *state) {
    SD_Call(0xB4);
    state->unk_10 = &update_message_window;
}
