#include "common.h"

typedef struct RuntimeState {
    u8 pad0[0x1C];
    u8 *cursor;
    u8 pad20[0x60];
    u8 *base;
} RuntimeState;

void func_8003A2E0(RuntimeState *arg0) {
    u8 *dst;
    u8 *src;
    u8 *after;
    u32 cursor;
    u32 index;
    u32 offset;
    u32 byte0;
    u32 byte1;
    u32 byte2;
    u32 byte3;

    cursor = (u32)arg0->cursor;
    index = *(u8 *)cursor;
    cursor++;
    arg0->cursor = (u8 *)cursor;
    offset = *(u8 *)cursor;
    after = (u8 *)(cursor + 1);
    arg0->cursor = after;

    byte0 = *(u8 *)(cursor + 1);
    byte1 = after[1];
    byte2 = after[2];
    byte3 = after[3];
    arg0->cursor = (u8 *)(cursor + 5);

    offset *= 4;
    dst = (u8 *)(byte0 + (byte1 << 8) +
                 (byte2 << 16) + (byte3 << 24) +
                 offset);
    src = (u8 *)((index * 4) + (u32)arg0->base);

    dst[0] = *(s32 *)(src + 0x48);
    dst[1] = *(s32 *)(src + 0x48) >> 8;
    dst[2] = *(s32 *)(src + 0x48) >> 16;
    dst[3] = *(s32 *)(src + 0x48) >> 24;
}
