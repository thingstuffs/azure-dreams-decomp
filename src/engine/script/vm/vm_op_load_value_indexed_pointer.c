#include "common.h"
#include "engine/script.h"
#include "engine/script/vm.h"

/* Opcode 0x4F: Load through a pointer table: v[var] = *LE32(addr32 + 4 * v[index]). */
void script_load_indirect_by_variable(MessageWindow *state) {
    u8 *cursor;
    u8 *addr_bytes;
    ScriptController *table;
    u8 *entry;
    u32 dst_index;
    u32 src_index;
    u32 entry_offset;
    u32 base_addr;
    u32 value_addr;

    cursor = state->cursor;
    dst_index = *cursor;
    cursor++;
    state->cursor = cursor;
    src_index = *cursor;
    table = state->controller;
    entry_offset = table->variables[src_index];
    addr_bytes = cursor + 1;
    state->cursor = addr_bytes;
    entry_offset <<= 2;
    base_addr = (u32)cursor[1]
    + ((u32)addr_bytes[1] << 8)
    + ((u32)addr_bytes[2] << 16)
    + ((u32)addr_bytes[3] << 24);
    state->cursor = cursor + 5;
    entry = (u8 *)(base_addr + entry_offset);
    value_addr = entry[0];
    value_addr += (u32)entry[1] << 8;
    value_addr += (u32)entry[2] << 16;
    value_addr += (u32)entry[3] << 24;
    table->variables[dst_index] = *(u32 *)value_addr;
}
