#include "common.h"

#include "common.h"

typedef s32 (*Func80039E1CHandler)(u32, u32, u32, u32);

typedef struct Func80039E1CTable {
    u8 pad_00[0x48];
    u32 arg0;
    u32 arg1;
    u32 arg2;
    u32 arg3;
    u8 pad_58[0x2C];
    s32 result;
} Func80039E1CTable;

typedef struct Func80039E1CReader {
    u8 pad_00[0x1C];
    u8 *read_ptr;
    u8 pad_20[0x60];
    Func80039E1CTable *table;
} Func80039E1CReader;

/* Read a handler index and table reference, call the handler, and store its result. */
void func_80039E1C(Func80039E1CReader *reader) {
    u8 *read_ptr = reader->read_ptr;
    Func80039E1CTable *table = reader->table;
    u8 handler_index = *read_ptr++;
    u8 *table_ref;
    Func80039E1CHandler *handlers;

    reader->read_ptr = read_ptr;
    table_ref = (u8 *)(read_ptr[0] + (read_ptr[1] << 8) +
                      (read_ptr[2] << 16) + (read_ptr[3] << 24));
    read_ptr += 4;
    handlers = (Func80039E1CHandler *)(table_ref[0] + (table_ref[1] << 8) +
                                     (table_ref[2] << 16) + (table_ref[3] << 24));
    reader->read_ptr = read_ptr;
    table->result = handlers[handler_index](table->arg0, table->arg1,
                                           table->arg2, table->arg3);
}
