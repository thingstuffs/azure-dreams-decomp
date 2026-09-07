#include "common.h"

typedef struct Func8003AA84Entry {
    u8 pad_00[0x48];
    u8 *next;
} Func8003AA84Entry;

typedef struct Func8003AA84State {
    u8 pad_00[0x1C];
    u8 *read_ptr;
    u8 pad_20[0x5C];
    u8 **write_ptr;
    u8 **table;
} Func8003AA84State;

u8 *func_8003AA84(Func8003AA84State *arg0) {
    u8 *read_ptr = arg0->read_ptr;
    u8 **table = arg0->table;
    u8 **write_ptr = arg0->write_ptr;
    u8 index = *read_ptr++;
    u8 *next;

    arg0->read_ptr = read_ptr;
    *write_ptr = read_ptr;
    arg0->write_ptr += 1;
    next = table[index + 18];
    arg0->read_ptr = next;
    return next;
}
