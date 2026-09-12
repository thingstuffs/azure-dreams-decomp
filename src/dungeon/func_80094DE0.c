#include "common.h"

extern s32 func_8009A350(s16, s16, s32, s32 *);
extern s16 func_800BCB04(u16, u16, s16);
extern u16 D_800DCEAC[];
extern u16 D_800DCEBC[];

/* Checks the sides of a diagonal direction for terrain above 0x200. */
s32 func_8009A540(s32 direction, s16 tile_x, s16 tile_y, s16 height)
{
    s32 tile_flags;
    s32 side_offset;
    s32 center_x;
    s32 center_y;
    s32 side_blocked;
    s32 x;
    s32 y;
    register u16 *x_offsets ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u16 *x_offset_ptr;
    u16 *y_offsets;
    u32 side_dir;
    u32 x_offset;
    u32 y_offset;
    s32 probe_height;
    register s32 saved_direction ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s16 saved_height ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u32 table_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    saved_direction = direction;
    saved_height = height;
    direction &= 1;
    if (direction) {
        ASM_KEEP(saved_direction);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(saved_height);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        side_offset = -1;
        x = (s16)tile_x;
        center_x = (x << 6) + 0x20;
        do {
            table_page = 0x800E0000;
        } while (0);
        ASM_KEEP(table_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        x_offsets = (u16 *)(table_page - 0x3154);
        y = (s16)tile_y;
        center_y = (y << 6) + 0x20;
loop:
        if ((func_8009A350(x, y, (saved_direction + side_offset) & 7, &tile_flags) << 16) == 0) {
            goto next;
        }
        side_dir = ((u16)saved_direction + side_offset) & 7;
        x_offset_ptr = (u16 *)((side_dir << 1) + (u32)x_offsets);
        probe_height = (s16)saved_height;
        x_offset = *x_offset_ptr;
        y_offsets = D_800DCEBC;
        ASM_KEEP(y_offsets);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        y_offset = y_offsets[side_dir];
        if (func_800BCB04(
                (x_offset + center_x) & 0xFFFF,
                (y_offset + center_y) & 0xFFFF,
                probe_height) >= 0x201) {
            side_blocked = side_offset < 2;
            goto decision;
        } else {
next:
            side_offset += 2;
            if (side_offset < 2) {
                goto loop;
            }
            ASM_KEEP(side_offset);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            side_blocked = side_offset < 2;
        }
decision:
        if (side_blocked) {
            return 0;
        }
    }
    return 1;
}

