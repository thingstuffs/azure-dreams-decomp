#include "common.h"

#include "common.h"

typedef struct Func8003A7FCTable {
    u8 pad_00[0x48];
    u32 values[256];
} Func8003A7FCTable;

typedef struct Func8003A7FCState {
    u8 pad_00[0x1C];
    u8 *read_ptr;
    u8 pad_20[0x60];
    Func8003A7FCTable *table;
} Func8003A7FCState;

void func_8003A7FC(Func8003A7FCState *arg0) {
    u8 *ptr = arg0->read_ptr;
    Func8003A7FCTable *table = arg0->table;
    u8 index = *ptr++;

    arg0->read_ptr = ptr;
    table->values[index] = ptr[0] + (ptr[1] << 8) +
                           (ptr[2] << 16) + (ptr[3] << 24);

    arg0->read_ptr += 4;
}
