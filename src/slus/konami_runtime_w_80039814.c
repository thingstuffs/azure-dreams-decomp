#include "common.h"

typedef struct {
    u8 pad[0x1c];
    u8 *read_ptr;
} ParserState;

extern u8 *func_8003C8E4(s32 arg0);

void func_80039814(ParserState *arg0)
{
    u8 value;
    u8 next_value;
    u8 *entry;

    value = arg0->read_ptr[0];
    arg0->read_ptr = arg0->read_ptr + 1;
    entry = func_8003C8E4(value);
    if (entry != 0) {
        next_value = arg0->read_ptr[0];
        entry[2] = next_value;
        entry[3] = next_value;
    }
    arg0->read_ptr = arg0->read_ptr + 1;
}
