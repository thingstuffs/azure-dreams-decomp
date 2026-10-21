#include "common.h"
#include "engine/audio.h"

typedef struct {
    u8 pad[0x1c];
    u8 *read_ptr;
} ParserState;

/* Read a script entry key and value, copying the value to entry bytes 2 and 3 if found. */
void vm_op_83_set_entry_byte_pair(ParserState *parser)
{
    u8 entry_key;
    u8 entry_value;
    u8 *entry;

    entry_key = parser->read_ptr[0];
    parser->read_ptr = parser->read_ptr + 1;
    entry = find_sound_table_entry(entry_key);
    if (entry != 0) {
        entry_value = parser->read_ptr[0];
        entry[2] = entry_value;
        entry[3] = entry_value;
    }
    parser->read_ptr = parser->read_ptr + 1;
}
