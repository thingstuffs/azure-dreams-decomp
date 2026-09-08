#include "common.h"

#include "common.h"

typedef s32 (*Func80039D48Handler)(u32, u32, u32, u32);

typedef struct Func80039D48Table {
    u8 pad_00[0x48];
    u32 arg0;
    u32 arg1;
    u32 arg2;
    u32 arg3;
    u8 pad_58[0x2C];
    s32 result;
} Func80039D48Table;

typedef struct Func80039D48Reader {
    u8 pad_00[0x1C];
    u8 *read_ptr;
    u8 pad_20[0x60];
    Func80039D48Table *table;
} Func80039D48Reader;

/* Read a little-endian handler address, call it with table arguments, and store the result. */
void func_80039D48(Func80039D48Reader *reader) {
    register u8 *read_ptr = reader->read_ptr;
    u32 addr_byte_0 = read_ptr[0];
    u32 addr_byte_1 = read_ptr[1];
    u32 addr_byte_2 = read_ptr[2];
    u32 addr_byte_3 = read_ptr[3];
    register Func80039D48Handler handler;
    Func80039D48Table *table = reader->table;

    handler = (Func80039D48Handler)(addr_byte_0 + (addr_byte_1 << 8) +
                                   (addr_byte_2 << 16) + (addr_byte_3 << 24));
    read_ptr += 4;
    reader->read_ptr = (u8 *)read_ptr;
    table->result = handler(table->arg0, table->arg1, table->arg2, table->arg3);
}
