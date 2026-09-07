#include "common.h"

#include "common.h"

typedef struct {
    u8 pad0[0x1C];
    u8 *volatile read_ptr;
    u8 pad20[0x60];
    u8 *table;
} Func8003A374State;

/* Copies a table word to the destination address selected by the command bytes. */
void func_8003A374(Func8003A374State *state) {
    u8 *cursor;
    u32 source_entry;
    u32 dest_offset;
    u32 dest_lookup;
    u8 *addr_bytes;
    u32 addr_byte1;
    u32 addr_byte2;
    u32 addr_byte3;
    u32 table_base;

    cursor = state->read_ptr;
    source_entry = cursor[0];
    cursor++;
    state->read_ptr = cursor;
    dest_offset = cursor[0];
    addr_bytes = cursor + 1;
    state->read_ptr = addr_bytes;
    dest_lookup = cursor[1];
    addr_byte1 = addr_bytes[1];
    addr_byte2 = addr_bytes[2];
    addr_byte3 = addr_bytes[3];
    state->read_ptr = cursor + 5;
    table_base = (u32)state->table;
    dest_offset <<= 2;
    addr_byte1 <<= 8;
    do {
        dest_lookup += addr_byte1;
    } while (0);
    addr_byte2 <<= 16;
    dest_lookup += addr_byte2;
    addr_byte3 <<= 24;
    dest_lookup += addr_byte3;
    dest_lookup += dest_offset;
    source_entry <<= 2;
    source_entry += table_base;
    *(s32 *)(u32)*(u8 *)dest_lookup =
        *(s32 *)(source_entry + 0x48);
}
