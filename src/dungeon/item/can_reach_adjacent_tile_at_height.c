#include "common.h"
#include "shared/dungeon_height_query.h"
#include "dungeon/item.h"
#include "dungeon/item/find_active_rect_containing_point_api.h"


/* Checks distinct neighboring positions for equal values or a successful fallback check. */
s32 can_reach_adjacent_tile_at_height(s16 x0, s16 y0, s16 check_param, s16 x1, s16 y1, s16 unused) {
    s32 dx;
    s32 dy;
    u16 query_aux;
    u16 start_x = x0;
    u16 start_y = y0;
    u16 end_x = x1;
    u16 end_y = y1;

    dx = __builtin_abs(x1 - x0);
    if (dx >= 2)
        return 0;
    dy = __builtin_abs(y1 - y0);
    if (!(dy >= 2 || dx + dy == 0)) {
        s16 start_room = find_active_rect_containing_point(start_x, start_y);
        s16 end_room = find_active_rect_containing_point(end_x, end_y);

        if (start_room == end_room) {
            return 1;
        }
        if ((s16)check_diagonal_side_height((get_rounded_facing_and_rounding_flag(x0, y0, x1, y1, &query_aux) << 16 >> 25) & 0xFFFF, x0, y0, check_param - 0x20) != 0) {
            return 1;
        }
    }
    return 0;
}
