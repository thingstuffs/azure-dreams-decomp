#include "common.h"
#include "engine/audio.h"

typedef struct {
    u8 pad[0x1c];
    u8 *read_ptr;
} ParserState;

/* Consumes a script entry key and value, storing the value in the entry's third byte if found. */
void vm_op_28_set_entry_byte(ParserState *parser)
{
    u8 entry_key;
    u8 *entry;

    entry_key = parser->read_ptr[0];
    parser->read_ptr = parser->read_ptr + 1;
    entry = find_sound_table_entry(entry_key);
    if (entry != 0) {
        entry[2] = parser->read_ptr[0];
    }
    parser->read_ptr = parser->read_ptr + 1;
}
