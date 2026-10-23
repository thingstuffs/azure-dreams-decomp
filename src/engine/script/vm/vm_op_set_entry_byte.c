#include "common.h"
#include "engine/script.h"
#include "engine/audio.h"

/* Consumes a script entry key and value, storing the value in the entry's third byte if found. */
void vm_op_28_set_entry_byte(ScriptReader *parser)
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
