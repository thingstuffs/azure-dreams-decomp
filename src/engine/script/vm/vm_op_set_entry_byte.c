#include "common.h"
#include "engine/script.h"
#include "engine/audio.h"

/* Opcode 0x1C: Set byte 2 of the sound-table entry selected by the u8 key. */
void script_set_sound_entry_byte(ScriptReader *parser)
{
    u8 entry_key;
    u8 *entry;

    entry_key = parser->cursor[0];
    parser->cursor = parser->cursor + 1;
    entry = find_sound_table_entry(entry_key);
    if (entry != 0) {
        entry[2] = parser->cursor[0];
    }
    parser->cursor = parser->cursor + 1;
}
