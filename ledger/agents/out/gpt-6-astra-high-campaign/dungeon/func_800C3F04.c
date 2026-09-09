#include "common.h"

extern void func_800C96E8();

/* Processes linked entries with position values staged in scratchpad memory. */
s32 func_800C9664(void *entry_data, void *position) {
    register u8 *data = entry_data;
    register u8 *scratch = (u8 *)0x1F800000;
    register u8 *next_node;
    s32 offset;

    for (;;) {
        offset = (s32)((u32)*(u16 *)data << 16) >> 17;
        *(u16 *)(scratch + 0xB8) = *(u16 *)((u8 *)position + 2) - offset;
        *(u16 *)(scratch + 0xBA) = *(u16 *)((u8 *)position + 6);
        *(s32 *)(scratch + 0xC0) = *(s16 *)((u8 *)position + 10);
        func_800C96E8(data, scratch);
        next_node = *(u8 **)(data - 8);
        if (next_node == 0) {
            break;
        }
        data = next_node + 0x20;
        position = *(u8 **)(next_node + 8);
    }
    return 0;
}
