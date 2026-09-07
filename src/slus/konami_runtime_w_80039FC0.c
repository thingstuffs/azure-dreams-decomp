#include "common.h"

#include "common.h"

typedef struct Func80039FC0Table {
    u8 pad_00[0x48];
    u32 values[256];
} Func80039FC0Table;

typedef struct Func80039FC0State {
    u8 pad_00[0x1C];
    u8 *read_ptr;
    u8 pad_20[0x60];
    Func80039FC0Table *table;
} Func80039FC0State;

void func_80039FC0(Func80039FC0State *arg0) {
    u8 *ptr = arg0->read_ptr;
    Func80039FC0Table *table = arg0->table;
    u8 index = *ptr++;

    arg0->read_ptr = ptr;
    table->values[index] = ptr[0] + (ptr[1] << 8) +
                           (ptr[2] << 16) + (ptr[3] << 24);

    arg0->read_ptr += 4;
}
