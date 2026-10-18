#include "common.h"
#include "shared/dir_step.h"

extern s16 find_active_rect_containing_point(s32, s32);

/* Finds the first neighboring direction with a negative probe result. */
s32 find_neighbor_with_negative_tile_probe(u8 *entity, s16 *direction) {
    s32 neighbor;

    for (neighbor = 0; neighbor < 8; neighbor++) {
        if (find_active_rect_containing_point((entity[0x24] + ((u16 *)dir_step_x)[neighbor]) & 0xFFFF,
                          (entity[0x25] + ((u16 *)dir_step_y)[neighbor]) & 0xFFFF) < 0) {
            *direction = neighbor << 9;
            return 1;
        }
    }
    return 0;
}
