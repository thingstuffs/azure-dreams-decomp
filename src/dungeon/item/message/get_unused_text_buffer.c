#include "dungeon/item/message.h"
#include "dungeon/data.h"
#include "engine/message/data.h"
#include "engine/message.h"

extern s32 battle_message_buffer_cursor[];

/* Cycle through the six buffers, skipping addresses queued in variables 10 through 14. */
void *get_unused_text_buffer(void) {
    s32 buffer_index;
    s32 entry_index;
    void *buffer;

    buffer_index = battle_message_buffer_cursor[0] = (battle_message_buffer_cursor[0] + 1) % 6;
    buffer = (buffer_index * 0x138) + battle_message_buffers;
    entry_index = 10;
    do {
        if (runtime_script_state.variables[entry_index] == (s32)buffer) {
            return get_unused_text_buffer();
        }
        entry_index++;
    } while (entry_index < 15);
    return buffer;
}
