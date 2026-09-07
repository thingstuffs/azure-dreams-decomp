#include "common.h"

typedef struct {
    u8 pad[0x1c];
    u8 *read_ptr;
} ParserState;

extern u8 *func_8003C8E4(s32 arg0);

void func_800397A8(ParserState *arg0)
{
    u8 value;
    u8 *entry;

    value = arg0->read_ptr[0];
    arg0->read_ptr = arg0->read_ptr + 1;
    entry = func_8003C8E4(value);
    if (entry != 0) {
        entry[2] = arg0->read_ptr[0];
    }
    arg0->read_ptr = arg0->read_ptr + 1;
}
