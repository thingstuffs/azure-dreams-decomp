#include "common.h"

typedef struct RuntimeState {
    u8 pad0[0x1C];
    u8 *cursor;
    u8 pad20[0x60];
    u8 *base;
} RuntimeState;

/* Stores an indexed runtime word in little-endian order at the destination read from the stream. */
void func_8003A2E0(RuntimeState *state) {
    u8 *dst;
    u8 *src;
    u8 *addr_bytes;
    u32 cursor;
    u32 src_index;
    u32 dst_offset;
    u32 addr_byte0;
    u32 addr_byte1;
    u32 addr_byte2;
    u32 addr_byte3;

    cursor = (u32)state->cursor;
    src_index = *(u8 *)cursor;
    cursor++;
    state->cursor = (u8 *)cursor;
    dst_offset = *(u8 *)cursor;
    addr_bytes = (u8 *)(cursor + 1);
    state->cursor = addr_bytes;

    addr_byte0 = *(u8 *)(cursor + 1);
    addr_byte1 = addr_bytes[1];
    addr_byte2 = addr_bytes[2];
    addr_byte3 = addr_bytes[3];
    state->cursor = (u8 *)(cursor + 5);

    dst_offset *= 4;
    dst = (u8 *)(addr_byte0 + (addr_byte1 << 8) +
                 (addr_byte2 << 16) + (addr_byte3 << 24) +
                 dst_offset);
    src = (u8 *)((src_index * 4) + (u32)state->base);

    dst[0] = *(s32 *)(src + 0x48);
    dst[1] = *(s32 *)(src + 0x48) >> 8;
    dst[2] = *(s32 *)(src + 0x48) >> 16;
    dst[3] = *(s32 *)(src + 0x48) >> 24;
}
