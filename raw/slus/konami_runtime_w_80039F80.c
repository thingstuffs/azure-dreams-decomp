#include "common.h"

typedef struct {
    u8 pad[0x48];
    u32 values[256];
} Table;

typedef struct {
    u8 pad_00[0x1C];
    u8 *read_ptr;
    u8 pad_20[0x60];
    Table *table;
} Reader;

void func_80039F80(Reader *reader) {
    u8 *ptr = reader->read_ptr;
    u8 first;
    u8 second;

    first = *ptr;
    ptr += 1;
    reader->read_ptr = ptr;
    second = *ptr;
    ptr += 1;
    reader->read_ptr = ptr;
    reader->table->values[first] = reader->table->values[second];
}
