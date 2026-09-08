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

/* Redirects the event script stream to the table entry selected by the next byte. */
void func_8003A9B8(Func8003A9B8State *vm) {
    u8 index = *vm->stream;
    vm->stream++;
    vm->stream = vm->table->values[index];
}
