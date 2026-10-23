#include "common.h"
#include "engine/script.h"

#include "common.h"

/* Store a VM table word at the address held in a byte selected by an immediate word offset. */
void handle_vm_opcode_78(ScriptReader *state) {
    u8 *cursor;
    u32 source_entry;
    u32 dest_offset;
    u32 dest_lookup;
    u8 *addr_bytes;
    u32 addr_byte1;
    u32 addr_byte2;
    u32 addr_byte3;
    u32 table_base;

    cursor = state->cursor;
    source_entry = cursor[0];
    cursor++;
    state->cursor = cursor;
    dest_offset = cursor[0];
    addr_bytes = cursor + 1;
    state->cursor = addr_bytes;
    dest_lookup = cursor[1];
    addr_byte1 = addr_bytes[1];
    addr_byte2 = addr_bytes[2];
    addr_byte3 = addr_bytes[3];
    state->cursor = cursor + 5;
    table_base = (u32)state->data;
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
