#include "common.h"
#include "m2c_compat.h"
#include "town/map/position.h"

s16 *town_map_mod_read_p();                       /* extern */


/* Writes four values to a square spaced 0x40 units apart ending at the given position. */
void write_square_position_offsets(s16 top_left, s16 top_right, s16 bottom_left, s16 bottom_right, TownPositionXY *pos) {
    *town_map_mod_read_p((s16) (pos->x_integer - 0x40), (s16) (pos->y_integer - 0x40)) = top_left;
    *town_map_mod_read_p((s16) pos->x_integer, (s16) (pos->y_integer - 0x40)) = top_right;
    *town_map_mod_read_p((s16) (pos->x_integer - 0x40), (s16) pos->y_integer) = bottom_left;
    *town_map_mod_read_p((s16) pos->x_integer, (s16) pos->y_integer) = bottom_right;
}
