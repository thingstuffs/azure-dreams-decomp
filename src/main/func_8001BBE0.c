#include "common.h"

extern s32 func_80051B50(void *arg0, s32 arg1, s32 arg2);
extern u8 D_80408B2C[];

void func_80402BE0(u8 *arg0)
{
    s32 i;
    s32 draw_offset;
    s32 vertical_offset;
    u8 *scan;
    u8 *item;
    u32 index_address;
    u32 row_address;
    u8 *table;

    i = 0;
    table = D_80408B2C;
    draw_offset = 0x234;
    vertical_offset = 0;
    scan = arg0;
    do {
        u8 *draw;

        draw = arg0 + draw_offset;
        draw_offset += 0x108;
        item = *(u8 **)(scan + 0x68C);
        scan += 4;
        *(s16 *)(*(u8 **)(item + 4) + 8) = 0x124 - (*(s32 *)(arg0 + 0x18) / 2);
        index_address = (u32)(i * 4);
        *(s16 *)(*(u8 **)(item + 4) + 0xA) = vertical_offset - (*(s32 *)(arg0 + 0x1C) / 2) + 0xFC;
        i++;
        vertical_offset += 0x11;
        row_address = (u32)(*(s32 *)(arg0 + 8) * 0x10);
        row_address += (u32)(unsigned long)table;
        index_address += row_address;
        *(s32 *)item = func_80051B50(
            draw,
            *(s32 *)(unsigned long)index_address,
            1);
    } while (i < 4);
}
