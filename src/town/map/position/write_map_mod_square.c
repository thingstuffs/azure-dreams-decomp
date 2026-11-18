#include "common.h"
#include "shared/entity.h"
#include "town/map/position.h"
#include "town.h"

/* Writes four values to a square spaced 0x40 units apart ending at the given position. */
void write_map_mod_square(s16 top_left, s16 top_right, s16 bottom_left, s16 bottom_right, ObjectPosition *pos) {
    *town_map_mod_read_p(pos->x.w.i - 0x40, pos->y.w.i - 0x40) = top_left;
    *town_map_mod_read_p(pos->x.w.i, pos->y.w.i - 0x40) = top_right;
    *town_map_mod_read_p(pos->x.w.i - 0x40, pos->y.w.i) = bottom_left;
    *town_map_mod_read_p(pos->x.w.i, pos->y.w.i) = bottom_right;
}
