#include "common.h"

#include "common.h"
#include "engine/script/vm.h"

typedef s32 (*Func80039E1CHandler)(u32, u32, u32, u32);

typedef struct Func80039E1CTable {
    u8 pad_00[0x48];
    u32 handler_arg0;
    u32 handler_arg1;
    u32 handler_arg2;
    u32 handler_arg3;
    u8 pad_58[0x2C];
    s32 result;
} Func80039E1CTable;

typedef struct Func80039E1CReader {
    u8 pad_00[0x1C];
    u8 *read_ptr;
    u8 pad_20[0x60];
    Func80039E1CTable *table;
} Func80039E1CReader;

/* Opcode 0x2F: Call entry u8 of the handler table whose pointer is stored at the 32-bit address, with v0..v3; result to v15. */
void script_call_service_from_table(Func80039E1CReader *reader) {
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
    table->result = handlers[handler_index](table->handler_arg0, table->handler_arg1,
                                            table->handler_arg2, table->handler_arg3);
}
