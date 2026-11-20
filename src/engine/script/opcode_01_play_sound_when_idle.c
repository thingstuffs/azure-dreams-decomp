#include "shared/audio_commands.h"
#include "engine/message.h"
#include "engine/script.h"
#include "engine/script/vm.h"
#include "slus.h"
#include "slus/runtime_directory.h"

/* Opcode 0x01: End of message: unless dispatch mode is 2, rewind while the sound status is 0x100, then send SD_Call(AUDIO_MESSAGE_END); park the window. */
void script_end_message(MessageWindow *window) {
    if (runtime_dispatch_mode_alias[0] != 2) {
        if (read_sound_mode_blocking_status(4) != 0x100) {
            SD_Call(AUDIO_MESSAGE_END);
        } else {
            window->message_handler = 0;
            window->cursor--;
            return;
        }
    }
    window->message_handler = noop_runtime_record_idle;
}
