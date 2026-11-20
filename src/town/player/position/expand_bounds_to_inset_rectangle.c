#include "common.h"
#include "town/map/variant_data.h"
#include "town/player/position.h"

/* Expands fixed-point bounds to include the inset rectangle. */
void expand_bounds_to_inset_rectangle(s32 *bounds, TownRectangle *rect) {
    s32 left;
    s32 top;
    s32 right;
    s32 bottom;

    left = (s16)rect->origin_x + rect->x_offset;
    top = (s16)rect->origin_y + rect->y_offset;
    right = left + rect->width;
    bottom = top + rect->height;
    top <<= 16;
    right <<= 16;
    bottom <<= 16;
    left = (left << 16) + 0x1FFFFF;
    top += 0x1FFFFF;
    right += 0xFFE00000;
    bottom += 0xFFEC0000;
    if (left < bounds[0]) {
        bounds[0] = left;
    }
    if (top < bounds[2]) {
        bounds[2] = top;
    }
    if (bounds[1] < right) {
        bounds[1] = right;
    }
    if (bounds[3] < bottom) {
        bounds[3] = bottom;
    }
}
