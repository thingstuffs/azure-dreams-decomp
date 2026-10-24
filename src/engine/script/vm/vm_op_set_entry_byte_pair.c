#include "common.h"
#include "engine/script.h"
#include "engine/audio.h"

/* Opcode 0x53: Set bytes 2 and 3 of the sound-table entry selected by the u8 key. */
void script_set_sound_entry_bytes(ScriptReader *parser)
{
    u8 entry_key;
    u8 entry_value;
    u8 *entry;

    entry_key = parser->cursor[0];
    parser->cursor = parser->cursor + 1;
    entry = find_sound_table_entry(entry_key);
    if (entry != 0) {
        entry_value = parser->cursor[0];
        entry[2] = entry_value;
        entry[3] = entry_value;
    }
    parser->cursor = parser->cursor + 1;
}
