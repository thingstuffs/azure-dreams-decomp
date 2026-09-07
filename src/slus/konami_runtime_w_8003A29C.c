#include "common.h"

typedef struct Func8003A29CTable {
    u8 pad_00[0x44];
    u32 **targets;
    u32 values[1];
} Func8003A29CTable;

typedef struct Func8003A29CState {
    u8 pad_00[0x1C];
    u8 *cursor;
    u8 pad_20[0x60];
    Func8003A29CTable *table;
} Func8003A29CState;

void func_8003A29C(Func8003A29CState *arg0) {
    u8 *cursor = arg0->cursor;
    u8 first;
    u8 second;
    Func8003A29CTable *table = arg0->table;

    first = *cursor++;
    arg0->cursor = cursor;
    second = *cursor++;
    arg0->cursor = cursor;
    table->targets[second][0] = table->values[first];
}
