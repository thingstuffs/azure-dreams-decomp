#include "common.h"

#include "common.h"

typedef struct {
    u8 pad_00[0x1C];
    u8 *read_ptr;
    u8 pad_20[0x60];
    u8 *values;
} Func8003A904State;

/* Handle an event-script table read by loading a little-endian word into the destination value slot. */
void func_8003A904(Func8003A904State *state) {
    u8 *operands;
    u8 *address_bytes;
    u8 *entry;
    u8 *values;
    u32 dst_index;
    u32 src_index;
    u32 table_offset;
    u32 address_byte_2;
    u32 value;

    operands = state->read_ptr;
    dst_index = operands[0];
    values = state->values;
    operands = operands + 1;
    state->read_ptr = operands;
    src_index = operands[0];
    address_bytes = operands + 1;
    state->read_ptr = address_bytes;

    table_offset = *(u32 *)(values + (src_index * 4) + 0x48);
    address_byte_2 = address_bytes[2];
    table_offset <<= 2;
    entry = (u8 *)((u32)operands[1] + ((u32)address_bytes[1] << 8)
               + (address_byte_2 << 16) + ((u32)address_bytes[3] << 24)
               + table_offset);
    state->read_ptr = operands + 5;

    value = entry[0];
    *(u32 *)(values + (dst_index * 4) + 0x48) = value;
    value += (u32)entry[1] << 8;
    *(u32 *)(values + (dst_index * 4) + 0x48) = value;
    value += (u32)entry[2] << 16;
    *(u32 *)(values + (dst_index * 4) + 0x48) = value;
    value += (u32)entry[3] << 24;
    *(u32 *)(values + (dst_index * 4) + 0x48) = value;
}
