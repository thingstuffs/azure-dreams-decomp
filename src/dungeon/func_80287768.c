#include "common.h"

extern s32 D_8001F660;
extern s32 D_8001F664;
extern s8 D_8001F66C[];
extern u8 D_8001F6A0;
extern s8 D_8001F6A4[];
extern s8 D_8001F6E8[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];

extern s32 func_8001ABC8(s16 arg0, s16 arg1);
extern s32 func_800A6D30(void);

/* Search outward for an eligible tile, updating the facing direction when turning. */
s16 func_8001A768(u16 *facing, s32 origin_x, s32 origin_y, s8 *tiles, s32 search_arg, s32 radius,
                  s32 filter_arg) {
    u16 start_x;
    u16 start_y;
    u16 saved_radius;
    u16 saved_filter;
    register s32 tile_filter ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 forward_limit;
    s32 search_radius;
    s32 facing_high;
    s32 facing_offset;
    register u16 tile_index_u16 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 initial_x_steps;
    s32 x;
    s32 y;
    s32 failures;
    register s32 tile_index ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s8 tile;
    s32 forward_steps;
    s32 sides_left;
    s32 side;
    s32 side_steps;
    s32 turn_dir;
    s32 forward_dir;
    s32 forward_offset;
    s32 turn_offset;
    u16 next_x;
    u16 next_y;
    s32 x_steps_base;
    s32 y_steps_base;
    s8 *blocked;
    s8 *map_base;
    s8 *side_marks;

    facing_high = (s32)*facing << 16;
    initial_x_steps = (s32)D_8006CCD8;
    facing_offset = facing_high >> 15;
    start_x = origin_x;
    start_y = origin_y;
    saved_radius = radius;
    failures = 0;
    x = origin_x + *(u16 *)(initial_x_steps + facing_offset) * radius;
    y = origin_y + *(u16 *)(D_8006CCE8 + facing_offset) * radius;
    tile_filter = filter_arg;
    saved_filter = tile_filter;

    if (((s16)x >= 0) && ((s16)x < D_8001F660) && ((s16)y >= 0) &&
        ((s16)y < D_8001F664) && (D_8001F6A4[facing_high >> 17] == 0)) {
        tile_index_u16 = x + (s16)y * D_8001F660;
        tile_index = (s16)tile_index_u16;
        tile = tiles[tile_index];
        if (tile > 0) {
            if (func_8001ABC8(tile_index, (s16)tile_filter) == 0) {
                return tile_index;
            }
            failures = 1;
        } else if (tile < 0) {
            failures = 1;
        }
    } else {
        failures++;
    }

    if (failures != 0) {
        D_8001F6A4[((s32)*facing << 16) >> 17] = 1;
        if ((s16)saved_radius < (s8)D_8001F6A0) {
            D_8001F6A0 = saved_radius;
        }
    }

    if ((s16)saved_radius > (s8)D_8001F6A0) {
        forward_limit = (s8)D_8001F6A0;
    } else {
        forward_limit = (s16)saved_radius;
    }

    forward_steps = 1;
    if (forward_steps < (s16)saved_radius) {
        search_radius = (s16)saved_radius;
        do {
            sides_left = 2;
            if (forward_steps >= forward_limit) {
                failures++;
                goto outer_next;
            }
            side_steps = search_radius - forward_steps;
            side = func_800A6D30() & 1;
            x_steps_base = (s32)D_8006CCD8;
            y_steps_base = (s32)D_8006CCE8;
            do {
                forward_dir = *(s16 *)facing;
                forward_offset = forward_dir * 2;
                turn_dir = (forward_dir + D_8001F66C[side]) & 6;
                turn_offset = turn_dir * 2;
                next_x = start_x + *(s16 *)(forward_offset + x_steps_base) * forward_steps
                                 + *(s16 *)(turn_offset + x_steps_base) * side_steps;
                next_y = start_y + *(s16 *)(forward_offset + y_steps_base) * forward_steps
                                 + *(s16 *)(turn_offset + y_steps_base) * side_steps;
                if (((s16)next_x >= 0) && ((s16)next_x < D_8001F660) &&
                    ((s16)next_y >= 0) && ((s16)next_y < D_8001F664)) {
                    map_base = D_8001F6E8;
                    side_marks = map_base + side * 4;
                    blocked = side_marks + forward_steps;
                    if (*blocked == 0) {
                        tile_index_u16 = next_x + (s16)next_y * D_8001F660;
                        tile_index = (s16)tile_index_u16;
                        map_base = tiles;
                        tile = map_base[tile_index];
                        if (tile == 0) {
                            goto next;
                        }
                        if (tile > 0) {
                            if (func_8001ABC8(tile_index, (s16)saved_filter) == 0) {
                                goto found;
                            }
                        }
                        *blocked = 1;
                    }
                }
                failures++;
            next:
                side ^= 1;
            } while (--sides_left > 0);
outer_next:
            forward_steps++;
        } while (forward_steps < search_radius);
    }

    if (failures < 3) {
        goto recurse;
    }
    return -1;
found:
    *facing = turn_dir;
    return tile_index;
recurse:
    return func_8001A768(facing, (s16)start_x, (s16)start_y, tiles, search_arg,
                         (s16)(saved_radius + 1), (s16)saved_filter);
}
