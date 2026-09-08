#include "common.h"

#include "common.h"

typedef struct {
    u8 pad_00[0x1C];
    u8 *read_ptr;
    u8 pad_20[0x60];
    u32 *values;
} Func8003A858State;

/* Loads an indexed little-endian word from the encoded address into a state value slot. */
void func_8003A858(Func8003A858State *state) {
    u8 *cursor;
    u8 *address_bytes;
    u8 dst_index;
    u8 src_index;
    u32 src_offset;
    u32 base_address;

    cursor = state->read_ptr;
    dst_index = cursor[0];
    cursor = cursor + 1;
    state->read_ptr = cursor;
    src_index = cursor[0];
    address_bytes = cursor + 1;
    state->read_ptr = address_bytes;
    src_offset = (u32)src_index << 2;

    base_address = (u32)cursor[1] + ((u32)address_bytes[1] << 8)
            + ((u32)address_bytes[2] << 16) + ((u32)address_bytes[3] << 24);
    state->read_ptr = cursor + 5;
    {
        u32 *values = state->values;
        u8 *src_bytes;

        values[dst_index + 18] = *(u8 *)(base_address + src_offset);
        src_bytes = (u8 *)(base_address + src_offset);
        values[dst_index + 18] += (u32)src_bytes[1] << 8;
        values[dst_index + 18] += (u32)src_bytes[2] << 16;
        values[dst_index + 18] += (u32)src_bytes[3] << 24;
    }
}
