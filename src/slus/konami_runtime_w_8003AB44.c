#include "common.h"

#include "common.h"

extern s32 D_8006A8C8[];
extern s32 D_8006A8DC[];
extern s32 func_8004D880(s32 arg0);
extern void func_8004D91C(s32 arg0, s16 *arg1);
extern void MoveImage(void *rect, s32 x, s32 y);

/* Copies an image to a table-spaced VRAM position when its destination X is in range. */
void func_8003AB44(u8 *image_code, s16 grid_x, s16 grid_y, s32 spacing, s16 base_x, s16 base_y)
{
    s16 rect[4];
    s32 dest_x;

    dest_x = base_x + grid_x * D_8006A8C8[spacing & 0xFF];
    if ((u32)(dest_x - 0x140) < 0x2C0) {
        func_8004D91C(func_8004D880(image_code[1] | (image_code[0] << 8)) & 0xFF, rect);
        MoveImage(rect, dest_x, base_y + grid_y * D_8006A8DC[spacing & 0xFF]);
    }
}
