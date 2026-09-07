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
    register s32 side_blocked ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s32 x;
    s32 y;
    register u16 *x_offsets ASM_REG("$23");   /* MATCH pin: retail register colouring depends on it */
    u16 *x_offset_ptr;
    u16 *y_offsets;
    u32 side_dir;
    u32 x_offset;
    u32 y_offset;
    s32 probe_height;
    register s32 saved_direction ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s16 saved_height ASM_REG("$22");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register u32 table_page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    saved_direction = direction;
    saved_height = height;
    direction &= 1;
    if (direction) {
        ASM_KEEP(saved_direction);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ASM_KEEP(saved_height);   /* MATCH pin: retail schedule: same instructions, different order without it */
        side_offset = -1;
        x = (s16)tile_x;
        center_x = (x << 6) + 0x20;
        ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
        table_page = 0x800E0000;
        ASM_KEEP(table_page);   /* MATCH pin: load-bearing for the whole function shape */
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
        ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
        y_offsets = D_800DCEBC;
        ASM_KEEP(y_offsets);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
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
            ASM_KEEP(side_offset);   /* MATCH pin: load-bearing for the whole function shape */
            side_blocked = side_offset < 2;
        }
decision:
        if (side_blocked) {
            return 0;
        }
    }
    return 1;
}

