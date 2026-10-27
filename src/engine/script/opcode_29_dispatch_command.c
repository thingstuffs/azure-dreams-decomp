#include "common.h"

#include "common.h"
#include "engine/script.h"
#include "slus.h"
#include "slus/data.h"

#include "engine/message.h"


/* Opcode 0x1D: Play a voice / CD audio cue (two 32-bit words) and send SD_Call(0x300); waits while sound is busy. */
void script_play_voice_cue(MessageVoiceState *owner)
{
    s32 runtime_state;
    s32 owner_gate;
    u8 *command_ptr;
    u8 *second_word_ptr;
    u32 command_word;
    u32 payload_word;
    u32 table_index;

    runtime_state = read_sound_mode_blocking_status(4);
    owner_gate = check_state_or_global_flags(owner);
    if (owner_gate != 0) {
        if (runtime_state != 0) {
            owner->action = 0;
            owner->cursor--;
            return;
        }
    } else if (runtime_state == 0x100 || runtime_state == 3) {
        owner->action = 0;
        owner->cursor--;
        return;
    }

    command_ptr = owner->cursor;
    command_word = command_ptr[0] + (command_ptr[1] << 8) +
            (command_ptr[2] << 16) + (command_ptr[3] << 24);
    second_word_ptr = command_ptr + 4;
    owner->cursor = second_word_ptr;
    payload_word = command_ptr[4] + (second_word_ptr[1] << 8) +
            (second_word_ptr[2] << 16) + (second_word_ptr[3] << 24);
    owner->cursor = command_ptr + 8;
    table_index = (command_word >> 19) & 0x1F;
    command_word &= 0xFF07FFFF;

    sound_set_cd_cue_parameters(owner->data[0x3C],
                  dispatch_entry_resource_values[script_command_resource_indices[table_index]],
                  command_word,
                  payload_word);
    SD_Call(0x300);
    owner->action = 0;
    return;
}
