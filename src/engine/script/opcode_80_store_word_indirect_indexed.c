#include "common.h"
#include "engine/script.h"

#include "common.h"

/* Store a VM table word at the address held in a byte selected by a table index value. */
void handle_vm_opcode_80(ScriptReader *state) {
    u8 *read_ptr;
    u8 *addr_bytes;
    u8 *table;
    u32 source_slot;
    u32 lookup_addr;
    u32 index_slot;
    u32 element_offset;
    u32 addr_byte_1;
    u32 addr_byte_2;
    u32 addr_byte_3;

    read_ptr = state->cursor;
    source_slot = read_ptr[0];
    read_ptr++;
    state->cursor = read_ptr;
    index_slot = read_ptr[0];
    table = state->data;
    index_slot <<= 2;
    index_slot += (u32)table;
    element_offset = *(u32 *)(index_slot + 0x48);
    addr_bytes = read_ptr + 1;
    state->cursor = addr_bytes;
    lookup_addr = read_ptr[1];
    read_ptr += 5;
    source_slot <<= 2;
    addr_byte_1 = addr_bytes[1];
    addr_byte_2 = addr_bytes[2];
    addr_byte_3 = addr_bytes[3];
    source_slot += (u32)table;
    state->cursor = read_ptr;
    do {
        element_offset <<= 2;
    } while (0);
    addr_byte_1 <<= 8;
    lookup_addr += addr_byte_1;
    addr_byte_2 <<= 16;
    lookup_addr += addr_byte_2;
    addr_byte_3 <<= 24;
    lookup_addr += addr_byte_3;
    lookup_addr += element_offset;
    *(s32 *)(u32)*(u8 *)lookup_addr =
        *(s32 *)(source_slot + 0x48);
}
