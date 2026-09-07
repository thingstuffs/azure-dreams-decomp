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

void func_80039D48(Func80039D48Reader *arg0) {
    register u8 *ptr = arg0->read_ptr;
    u32 byte0 = ptr[0];
    u32 byte1 = ptr[1];
    u32 byte2 = ptr[2];
    u32 byte3 = ptr[3];
    register Func80039D48Handler target;
    Func80039D48Table *table = arg0->table;

    target = (Func80039D48Handler)(byte0 + (byte1 << 8) +
                                   (byte2 << 16) + (byte3 << 24));
    ptr += 4;
    arg0->read_ptr = (u8 *)ptr;
    table->result = target(table->arg0, table->arg1, table->arg2, table->arg3);
}
