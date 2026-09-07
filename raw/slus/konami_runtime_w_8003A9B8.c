#include "common.h"

typedef struct Func8003A9B8Table {
    u8 pad_00[0x48];
    u8 *values[256];
} Func8003A9B8Table;

typedef struct Func8003A9B8State {
    u8 pad_00[0x1c];
    u8 *stream;
    u8 pad_20[0x60];
    Func8003A9B8Table *table;
} Func8003A9B8State;

void func_8003A9B8(Func8003A9B8State *arg0) {
    u8 index = *arg0->stream;
    arg0->stream++;
    arg0->stream = arg0->table->values[index];
}
