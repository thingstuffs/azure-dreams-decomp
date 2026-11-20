#include "common.h"

#include "dungeon/level.h"
#include "shared/dir_step.h"

extern u8 floor_objects[];

/* Find a record in the given direction and clear bit 0x80 if bit 0x40 is unset. */
s32 find_directional_entry_and_clear_flag(s32 origin_x, s32 origin_y, u32 direction, s16 search_param) {
    s32 offset_index;
    s16 record_index;
    u8 *table;
    u8 *record;
    u8 flags;

    offset_index = (direction >> 9) & 7;
    record_index = find_entry_at_tile_coordinates(
        (u16)dir_step_x[offset_index] + origin_x,
        (u16)dir_step_y[offset_index] + origin_y, search_param);
    if (record_index >= 0) {
        table = floor_objects;
        record = table + record_index * 4;
        flags = record[3];
        if (!(flags & 0x40)) {
            if (flags & 0x80) {
                record[3] = flags & 0x7F;
                return record_index;
            }
        }
    }
    return -1;
}
