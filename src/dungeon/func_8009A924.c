#include "common.h"
#include "shared/dir_step.h"

extern s16 find_active_rect_containing_point(s32, s32);

/* Finds a valid neighboring direction and reports whether one was found. */
s32 find_neighbor_with_nonnegative_tile_probe(u8 *object, s16 *direction_out) {
    s32 direction;

    for (direction = 0; direction < 8; direction++) {
        if (find_active_rect_containing_point((object[0x24] + ((u16 *)dir_step_x)[direction]) & 0xFFFF,
                          (object[0x25] + ((u16 *)dir_step_y)[direction]) & 0xFFFF) >= 0) {
            *direction_out = direction << 9;
            return 1;
        }
    }
    return 0;
}
