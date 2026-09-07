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

void func_80039E1C(Func80039E1CReader *arg0) {
    u8 *ptr = arg0->read_ptr;
    Func80039E1CTable *table = arg0->table;
    u8 index = *ptr++;
    u8 *data;
    Func80039E1CHandler *handlers;

    arg0->read_ptr = ptr;
    data = (u8 *)(ptr[0] + (ptr[1] << 8) +
                  (ptr[2] << 16) + (ptr[3] << 24));
    ptr += 4;
    handlers = (Func80039E1CHandler *)(data[0] + (data[1] << 8) +
                                       (data[2] << 16) + (data[3] << 24));
    arg0->read_ptr = ptr;
    table->result = handlers[index](table->arg0, table->arg1,
                                    table->arg2, table->arg3);
}
