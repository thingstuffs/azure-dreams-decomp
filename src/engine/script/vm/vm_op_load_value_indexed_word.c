#include "common.h"
#include "engine/script.h"

#include "common.h"

/* Opcode 0x47: Load word: v[var] = LE32(addr32 + 4 * v[index]). */
void script_load_table_word_by_variable(ScriptReader *state) {
    u8 *operands;
    u8 *address_bytes;
    u8 *entry;
    u8 *values;
    u32 dst_index;
    u32 src_index;
    u32 table_offset;
    u32 address_byte_2;
    u32 value;

    operands = state->cursor;
    dst_index = operands[0];
    values = state->data;
    operands = operands + 1;
    state->cursor = operands;
    src_index = operands[0];
    address_bytes = operands + 1;
    state->cursor = address_bytes;

    table_offset = *(u32 *)(values + (src_index * 4) + 0x48);
    address_byte_2 = address_bytes[2];
    table_offset <<= 2;
    entry = (u8 *)((u32)operands[1] + ((u32)address_bytes[1] << 8)
                   + (address_byte_2 << 16) + ((u32)address_bytes[3] << 24)
                   + table_offset);
    state->cursor = operands + 5;

    value = entry[0];
    *(u32 *)(values + (dst_index * 4) + 0x48) = value;
    value += (u32)entry[1] << 8;
    *(u32 *)(values + (dst_index * 4) + 0x48) = value;
    value += (u32)entry[2] << 16;
    *(u32 *)(values + (dst_index * 4) + 0x48) = value;
    value += (u32)entry[3] << 24;
    *(u32 *)(values + (dst_index * 4) + 0x48) = value;
}
