#include "common.h"

#include "common.h"

typedef s32 (*Func80039DBCHandler)(u32, u32, u32, u32);

typedef struct Func80039DBCTable {
    u8 pad_00[0x40];
    Func80039DBCHandler *handlers;
    u32 pad_44;
    u32 arg0;
    u32 arg1;
    u32 arg2;
    u32 arg3;
    u8 pad_58[0x2C];
    s32 result;
} Func80039DBCTable;

typedef struct Func80039DBCReader {
    u8 pad_00[0x1C];
    u8 *read_ptr;
    u8 pad_20[0x60];
    Func80039DBCTable *table;
} Func80039DBCReader;

void func_80039DBC(Func80039DBCReader *arg0) {
    u8 *ptr = arg0->read_ptr;
    Func80039DBCTable *table = arg0->table;
    u8 index = *ptr;
    Func80039DBCHandler *handlers = table->handlers;
    s32 result;

    ptr++;
    arg0->read_ptr = ptr;
    result = handlers[index](table->arg0, table->arg1, table->arg2, table->arg3);
    table->result = result;
}
