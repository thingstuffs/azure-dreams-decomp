#include "common.h"

typedef struct RuntimeState {
    u8 pad0[0x1C];
    u8 *read_ptr;
    u8 pad20[0x60];
    u8 *table;
} RuntimeState;

/* Load a table slot through an indexed pointer in the encoded address table. */
void func_8003A1A4(RuntimeState *state) {
    u8 *cursor;
    u8 *addr_bytes;
    u8 *table;
    u8 *entry;
    u32 dst_index;
    u32 src_index;
    u32 entry_offset;
    u32 base_addr;
    u32 value_addr;

    cursor = state->read_ptr;
    dst_index = *cursor;
    cursor++;
    state->read_ptr = cursor;
    src_index = *cursor;
    table = state->table;
    entry_offset = *(u32 *)(table + (src_index * 4) + 0x48);
    addr_bytes = cursor + 1;
    state->read_ptr = addr_bytes;
    entry_offset <<= 2;
    base_addr = (u32)cursor[1]
        + ((u32)addr_bytes[1] << 8)
        + ((u32)addr_bytes[2] << 16)
        + ((u32)addr_bytes[3] << 24);
    state->read_ptr = cursor + 5;
    entry = (u8 *)(base_addr + entry_offset);
    value_addr = (u32)entry[0]
        + ((u32)entry[1] << 8)
        + ((u32)entry[2] << 16)
        + ((u32)entry[3] << 24);
    *(u32 *)(table + (dst_index * 4) + 0x48) = *(u32 *)value_addr;
}
