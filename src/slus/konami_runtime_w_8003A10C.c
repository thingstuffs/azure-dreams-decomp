#include "common.h"

#include "common.h"

typedef struct {
    u8 pad_00[0x1C];
    u8 *read_ptr;
    u8 pad_20[0x60];
    u8 *values;
} Func8003A10CState;

/* Load a value through an indexed pointer table into the selected state slot. */
void func_8003A10C(Func8003A10CState *state) {
    u8 *table_entry;
    u8 *address_bytes;
    u8 *cursor;
    u8 dst_index;
    u32 table_offset;
    u32 table_addr;
    u32 value_addr;

    cursor = state->read_ptr;
    dst_index = cursor[0];
    cursor = cursor + 1;
    state->read_ptr = cursor;
    table_offset = cursor[0];
    address_bytes = cursor + 1;
    state->read_ptr = address_bytes;
    table_offset <<= 2;

    table_addr = (s32)cursor[1] + ((u32)address_bytes[1] << 8)
            + ((u32)address_bytes[2] << 16) + ((u32)address_bytes[3] << 24);
    state->read_ptr = cursor + 5;
    table_entry = (u8 *)(table_addr + table_offset);

    value_addr = (u32)table_entry[0] + ((u32)table_entry[1] << 8)
             + ((u32)table_entry[2] << 16) + ((u32)table_entry[3] << 24);
    *(u32 *)(state->values + 0x48 + (dst_index * 4)) = *(u32 *)value_addr;
}
