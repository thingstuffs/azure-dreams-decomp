#include "dungeon/level/generate.h"

s16 carve_corridor_toward_destination(floor_generate_isolated_802895E4_Pos *start, floor_generate_isolated_802895E4_Pos *dest, s16 rnd, s16 *out_x, s16 *out_y,
                  floor_generate_isolated_802895E4_Walker *walker, s32 *cost) {
    s16 count;
    s16 cx;
    s16 cy;
    s16 dir;
    s16 dst_x;
    s16 dst_y;
    s16 dir_slot;
    s16 range_x;
    s16 range_y;
    s16 wx;
    s16 wy;
    s32 delta;
    s32 delta2;
    s32 idy;
    GameWork *gw;
    MapGrid *st;
    u32 r;

    count = 0;
    cy = start->y;
    cx = start->x;
    delta = dest->x;
    delta = delta - cx;
    dir = start->dir;
    delta = abs(delta);
    range_x = delta - 4;
    gw = &g_game_work;
    dir_slot = dir;
    dst_y = dest->y;
    dst_x = dest->x;
    if (range_x <= 0) {
        range_x = 1;
    }
    st = &gw->map;
    wx = range_x;
    if (wx >= 5) {
        wx = 4;
    }
    range_x = range_x - wx;
    if (range_x <= 0) {
        range_x = 1;
    }

    idy = (u32)(u16)dst_y << 16;
    idy >>= 16;
    delta = (u32)(u16)cy << 16;
    delta >>= 16;
    delta2 = abs(idy - delta);
    range_y = delta2 - 4;
    if (range_y <= 0) {
        range_y = 1;
    }
    wy = range_y;
    if (wy >= 5) {
        wy = 4;
    }
    range_y = range_y - wy;
    if (range_y <= 0) {
        range_y = 1;
    }

    if (rnd != 0) {
        s16 r;

        r = (u16)generate_random_value() % range_x;
        *out_x = r;
        wx = cx + r * dir_step_x[dir] + dir_step_x[dir] * wx;
        r = (u16)generate_random_value() % range_y;
        *out_y = r;
        wy = cy + r * dir_step_y[dir] + dir_step_y[dir] * wy;
    } else {
        wx = cx + *out_x * dir_step_x[dir] + dir_step_x[dir] * wx;
        wy = cy + *out_y * dir_step_y[dir] + dir_step_y[dir] * wy;
    }

    for (;;) {
        s32 iy;
        s32 ix;
        s32 tile;
        floor_generate_isolated_802895E4_DungeonCell *cell;
        s32 d;

        tile = walker->tile & 0xFFE0;
        iy = cy;
        cell = &((floor_generate_isolated_802895E4_DungeonCell *)D_800EA000)[(iy << st->shiftX) + (ix = cx)];
        if (cell->value != 16384) {
            d = abs(cell->value - (s16)tile);
            if (d >= 33) {
                return -1;
            }
        }
        cell->value = tile;
        if (ix == wx && iy == wy) {
            break;
        }
        *(s32 *)walker += *cost;
        count++;
        cx += dir_step_x[dir];
        cy += dir_step_y[dir];
    }

    if (wx != dst_x || wy != dst_y) {
        if (dir_step_x[dir_slot] != 0) {
            wy = dst_y;
        } else {
            wx = dst_x;
        }
        r = forward_monster_coordinate_delta(cx, cy, wx, wy);
        dir = (r >> 9) & 6;
        for (;;) {
            s32 iy;
            s32 ix;
            s32 tile;
            floor_generate_isolated_802895E4_DungeonCell *cell;
            s32 d;

            tile = walker->tile & 0xFFE0;
            iy = cy;
            cell = &((floor_generate_isolated_802895E4_DungeonCell *)D_800EA000)[(iy << st->shiftX) + (ix = cx)];
            if (cell->value != 16384) {
                d = abs(cell->value - (s16)tile);
                if (d >= 33) {
                    return -1;
                }
            }
            cell->value = tile;
            if (ix == wx && iy == wy) {
                break;
            }
            *(s32 *)walker += *cost;
            count++;
            cx += dir_step_x[dir];
            cy += dir_step_y[dir];
        }
    }

    if (wx != dst_x || wy != dst_y) {
        r = forward_monster_coordinate_delta(cx, cy, dst_x, dst_y);
        dir = (r >> 9) & 6;
        for (;;) {
            s32 iy;
            s32 ix;
            s32 tile;
            floor_generate_isolated_802895E4_DungeonCell *cell;
            s32 d;

            tile = walker->tile & 0xFFE0;
            iy = cy;
            cell = &((floor_generate_isolated_802895E4_DungeonCell *)D_800EA000)[(iy << st->shiftX) + (ix = cx)];
            if (cell->value != 16384) {
                d = abs(cell->value - (s16)tile);
                if (d >= 33) {
                    return -1;
                }
            }
            cell->value = tile;
            if (ix == dst_x && iy == dst_y) {
                break;
            }
            *(s32 *)walker += *cost;
            count++;
            cx += dir_step_x[dir];
            cy += dir_step_y[dir];
        }
    }
    return count;
}
