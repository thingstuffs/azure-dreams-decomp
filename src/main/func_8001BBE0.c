#include "common.h"

extern s32 func_80051B50(void *arg0, s32 arg1, s32 arg2);
extern u8 D_80408B2C[];

/* Position and update four display items using the selected table row. */
void func_80402BE0(u8 *state)
{
    s32 item_index;
    s32 draw_offset;
    s32 vertical_offset;
    u8 *item_cursor;
    u8 *item;
    u32 entry_addr;
    u32 row_addr;
    u8 *item_table;

    item_index = 0;
    item_table = D_80408B2C;
    draw_offset = 0x234;
    vertical_offset = 0;
    item_cursor = state;
    do {
        u8 *draw_buffer;

        draw_buffer = state + draw_offset;
        draw_offset += 0x108;
        item = *(u8 **)(item_cursor + 0x68C);
        item_cursor += 4;
        *(s16 *)(*(u8 **)(item + 4) + 8) = 0x124 - (*(s32 *)(state + 0x18) / 2);
        entry_addr = (u32)(item_index * 4);
        *(s16 *)(*(u8 **)(item + 4) + 0xA) = vertical_offset - (*(s32 *)(state + 0x1C) / 2) + 0xFC;
        item_index++;
        vertical_offset += 0x11;
        row_addr = (u32)(*(s32 *)(state + 8) * 0x10);
        row_addr += (u32)(unsigned long)item_table;
        entry_addr += row_addr;
        *(s32 *)item = func_80051B50(
            draw_buffer,
            *(s32 *)(unsigned long)entry_addr,
            1);
    } while (item_index < 4);
}
