#include "common.h"

typedef struct Func8003A4B4Entry {
    u8 pad_00[0x48];
    s32 value[256];
} Func8003A4B4Entry;

typedef struct Func8003A4B4State {
    u8 pad_00[0x1c];
    u8 *read_ptr;
    u8 pad_20[0x60];
    Func8003A4B4Entry *table;
} Func8003A4B4State;

void func_8003A4B4(Func8003A4B4State *arg0) {
    u8 *ptr;
    s32 first;
    s32 second;
    Func8003A4B4Entry *table;

    ptr = arg0->read_ptr;
    first = *ptr;
    ptr++;
    arg0->read_ptr = ptr;
    second = *ptr;
    ptr++;
    arg0->read_ptr = ptr;

    table = arg0->table;
    table->value[first] = table->value[first] - table->value[second];
}
