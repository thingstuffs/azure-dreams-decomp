#include "common.h"
#include "dungeon/item.h"

extern s32 check_diagonal_side_height(s32 direction, s16 tile_x, s16 tile_y, s16 height);
extern s16 find_active_rect_containing_point(u16, u16);

/* Checks distinct neighboring positions for equal values or a successful fallback check. */
s32 check_monster_neighbor_relations(s16 x0, s16 y0, s16 check_param, s16 x1, s16 y1) {
    s32 dx;
    s32 dy;
    u16 query_aux;

    dx = __builtin_abs(x1 - x0);
    if (dx >= 2)
        return 0;
    dy = __builtin_abs(y1 - y0);
    if (!(dy >= 2 || dx + dy == 0)) {
        if (find_active_rect_containing_point(x0, y0) == find_active_rect_containing_point(x1, y1)) {
            return 1;
        }
        if ((s16)check_diagonal_side_height((get_rounded_facing_and_rounding_flag(x0, y0, x1, y1, &query_aux) << 16 >> 25) & 0xFFFF, x0, y0, check_param - 0x20) != 0) {
            return 1;
        }
    }
    return 0;
}
