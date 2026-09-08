#include "common.h"

typedef struct {
    u8 pad[0x1c];
    u8 *read_ptr;
} ParserState;

extern u8 *func_8003C8E4(s32 arg0);

/* Consume an entry key and a value, storing the value in the entry's third byte if found. */
void func_800397A8(ParserState *parser)
{
    u8 entry_key;
    u8 *entry;

    entry_key = parser->read_ptr[0];
    parser->read_ptr = parser->read_ptr + 1;
    entry = func_8003C8E4(entry_key);
    if (entry != 0) {
        entry[2] = parser->read_ptr[0];
    }
    parser->read_ptr = parser->read_ptr + 1;
}
