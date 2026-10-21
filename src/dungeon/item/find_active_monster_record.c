#include "common.h"
#include "shared/dungeon_floor.h"

extern s16 dungeon_room_count;

/* Return the first active record containing the coordinates, or -1 if none matches. */
s32 find_padded_rectangle(s32 pos_x, s32 pos_y) {
    u8 *record;
    s32 index;
    s32 initial_count;
    s32 result;
    s32 x;
    s32 y;
    s32 count;

    initial_count = dungeon_room_count;
    index = 0;
    if (initial_count > 0) {
        x = pos_x & 0xFFFF;
        y = pos_y & 0xFFFF;
        count = initial_count;
        do {
            record = (u8 *)dungeon_rooms + index * 20;
            if (*(s16 *)(record + 10) != 0) {
                u16 left = *(u16 *)(record + 0);
                if (x >= left - 1 && left + *(u16 *)(record + 4) >= x) {
                    u16 top = *(u16 *)(record + 2);
                    if (y >= top - 1 && top + *(u16 *)(record + 6) >= y) {
                        result = (s16)index;
                        return result;
                    }
                }
            }
            index++;
        } while (index < count);
    }
    result = -1;
    return result;
}
