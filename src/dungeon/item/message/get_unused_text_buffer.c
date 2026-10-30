#include "dungeon/item/message.h"

extern s32 runtime_script_state[];
extern s32 D_800DD718[];
extern u8 battle_message_buffers[];

/* Selects the next buffer not referenced by the five checked table entries. */
void *get_unused_text_buffer(void) {
    s32 buffer_index;
    s32 entry_index;
    void *buffer;
    s32 *entry;
    s32 *table;

    entry_index = 0xA;
    table = runtime_script_state;
    entry = table + 10;
    buffer_index = D_800DD718[0] = (D_800DD718[0] + 1) % 6;
    buffer = (buffer_index * 0x138) + battle_message_buffers;
    do {
        entry_index += 1;
        if (entry[18] == (s32)buffer) {
            return get_unused_text_buffer();
        }
        entry += 1;
    } while (entry_index < 0xF);
    return buffer;
}
