#include "common.h"

typedef struct RuntimeState {
    u8 pad0[0x1C];
    u8 *read_ptr;
    u8 pad20[0x60];
    u8 *table;
} RuntimeState;

void func_8003A1A4(RuntimeState *arg0) {
    u8 *cursor;
    u8 *payload;
    u8 *table;
    u8 *entry;
    u32 dst_index;
    u32 src_index;
    u32 table_value;
    u32 address;
    u32 indirect;

    cursor = arg0->read_ptr;
    dst_index = *cursor;
    cursor++;
    arg0->read_ptr = cursor;
    src_index = *cursor;
    table = arg0->table;
    table_value = *(u32 *)(table + (src_index * 4) + 0x48);
    payload = cursor + 1;
    arg0->read_ptr = payload;
    table_value <<= 2;
    address = (u32)cursor[1]
        + ((u32)payload[1] << 8)
        + ((u32)payload[2] << 16)
        + ((u32)payload[3] << 24);
    arg0->read_ptr = cursor + 5;
    entry = (u8 *)(address + table_value);
    indirect = (u32)entry[0]
        + ((u32)entry[1] << 8)
        + ((u32)entry[2] << 16)
        + ((u32)entry[3] << 24);
    *(u32 *)(table + (dst_index * 4) + 0x48) = *(u32 *)indirect;
}
