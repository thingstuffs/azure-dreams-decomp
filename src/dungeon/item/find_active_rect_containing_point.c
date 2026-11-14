#include "common.h"
#include "shared/dungeon_floor.h"
#include "dungeon/item.h"
#include "dungeon/item/find_active_rect_containing_point_api.h"

#include "dungeon/level/room_count_data.h"

/* Returns the first active rectangle containing the point, or -1 if none does. */
s32 find_active_rect_containing_point(s32 point_x, s32 point_y) {
    s32 index;

    for (index = 0; index < dungeon_room_count; index++) {
        DungeonRoom *room = &dungeon_rooms[index];

        if (room->active != 0 && (u16)point_x >= room->x && (u16)point_x < room->x + room->w &&
            (u16)point_y >= room->y && (u16)point_y < room->y + room->h) {
            return (s16)index;
        }
    }
    return -1;
}
