#include "common.h"
#include "engine/script.h"

#include "common.h"
#include "engine/script/vm.h"

/* Opcode 0x4D: Load through a pointer table: v[var] = *LE32(addr32 + 4 * u8). */
void script_load_indirect(ScriptReader *state) {
    u8 *table_entry;
    u8 *address_bytes;
    u8 *cursor;
    u8 dst_index;
    u32 table_offset;
    u32 table_addr;
    u32 value_addr;

    cursor = state->cursor;
    dst_index = cursor[0];
    cursor = cursor + 1;
    state->cursor = cursor;
    table_offset = cursor[0];
    address_bytes = cursor + 1;
    state->cursor = address_bytes;
    table_offset <<= 2;

    table_addr = (s32)cursor[1] + ((u32)address_bytes[1] << 8)
    + ((u32)address_bytes[2] << 16) + ((u32)address_bytes[3] << 24);
    state->cursor = cursor + 5;
    table_entry = (u8 *)(table_addr + table_offset);

    value_addr = (u32)table_entry[0] + ((u32)table_entry[1] << 8)
    + ((u32)table_entry[2] << 16) + ((u32)table_entry[3] << 24);
    *(u32 *)(state->data + 0x48 + (dst_index * 4)) = *(u32 *)value_addr;
}
