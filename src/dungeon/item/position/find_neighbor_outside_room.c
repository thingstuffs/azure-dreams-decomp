#include "common.h"
#include "shared/dir_step.h"
#include "dungeon/item/position.h"

#include "dungeon/item/find_active_rect_containing_point_api.h"

/* Finds the first neighboring direction with a negative probe result. */
s32 find_neighbor_outside_room(u8 *entity, s16 *direction) {
    s32 neighbor;

    for (neighbor = 0; neighbor < 8; neighbor++) {
        if ((s16)find_active_rect_containing_point((entity[0x24] + (u16)dir_step_x[neighbor]) & 0xFFFF,
                          (entity[0x25] + (u16)dir_step_y[neighbor]) & 0xFFFF) < 0) {
            *direction = neighbor << 9;
            return 1;
        }
    }
    return 0;
}
