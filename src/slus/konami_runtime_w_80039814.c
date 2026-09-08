#include "common.h"

typedef struct {
    u8 pad[0x1c];
    u8 *read_ptr;
} ParserState;

extern u8 *func_8003C8E4(s32 arg0);

/* Read a script entry key and value, copying the value to entry bytes 2 and 3 if found. */
void func_80039814(ParserState *parser)
{
    u8 entry_key;
    u8 entry_value;
    u8 *entry;

    entry_key = parser->read_ptr[0];
    parser->read_ptr = parser->read_ptr + 1;
    entry = func_8003C8E4(entry_key);
    if (entry != 0) {
        entry_value = parser->read_ptr[0];
        entry[2] = entry_value;
        entry[3] = entry_value;
    }
    parser->read_ptr = parser->read_ptr + 1;
}
