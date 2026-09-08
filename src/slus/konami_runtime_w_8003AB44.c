#include "common.h"

#include "common.h"

extern s32 D_8006A8C8[5];
extern s32 D_8006A8DC[5];
extern s32 func_8004D880(s32 arg0);
extern void func_8004D91C(s32 arg0, s16 *arg1);
extern void MoveImage(void *rect, s32 x, s32 y);

/* Copies an image to a table-spaced VRAM position when its destination X is in range. */
void func_8003AB44(u8 *image_code, s16 grid_x, s16 grid_y, s32 spacing, s16 base_x, s32 base_y)
{
    s16 rect[4];
    s32 spacing_index;
    s32 column;
    s32 row;
    s32 dest_x;
    s32 table_offset;
    volatile u8 *x_table;
    volatile u8 *y_table;

    column = grid_x;
    spacing_index = spacing & 0xFF;
    x_table = (volatile u8 *)D_8006A8C8;
    table_offset = spacing_index * 4;
    dest_x = base_x + column * *(volatile s32 *)(x_table + table_offset);
    if ((u32)(dest_x - 0x140) < 0x2C0) {
        func_8004D91C(func_8004D880(image_code[1] | (image_code[0] << 8)) & 0xFF, rect);
        row = grid_y;
        y_table = (volatile u8 *)D_8006A8DC;
        MoveImage(rect, dest_x, (s16)base_y + row * *(volatile s32 *)(y_table + table_offset));
    }
}
