#include "town/menu.h"
#include "common.h"
#include "town/map/variant_data.h"
#include "shared/entity.h"
#include "engine/resource.h"
#include "town/shop.h"
#include "town/shop/state_countdown_updates_g00558.h"
#include "town/data.h"

/* Return the nearest unflagged record's result, or -1 if none is available. */
s32 find_nearest_unflagged_record_result(s32 record_set, ObjectPosition *target)
{
    TownSpawnEntry *records;
    TownSpawnEntry *record;
    u8 *flag_base;
    s32 count;
    s32 best_distance;
    s32 record_index;
    s32 base_x;
    s32 base_y;
    s32 distance;
    s32 result;
    /* BYTES: load the origins before the count test and sign-extend them inside it. */
    u16 raw_x;
    u16 raw_y;

    best_distance = 0x7FFFFFFF;
    record_index = 0;
    count = town_record_capacities[record_set];
    {
        TownRectangle *rectangle = town_script_state_slots[0];

        records = rectangle->entry_list[1];
        raw_x = rectangle->origin_x;
        raw_y = rectangle->origin_y;
    }
    record_set = record_index;
    if (count > 0) {
        base_x = (s16)raw_x;
        base_y = (s16)raw_y;
        record = records;
        flag_base = (u8 *)0x80010000;
        do {
            if (flag_base[0x981] == 0) {
                distance = estimate_vector_length(
                    (((s16)record->x_offset + base_x) - target->x.w.i) << 16,
                    (((s16)record->y_offset + base_y) - target->y.w.i) << 16);
                if (distance < best_distance) {
                    best_distance = distance;
                    record_set = record_index;
                }
                record++;
            } else {
                record++;
            }
            record_index++;
            flag_base += 4;
        } while (record_index < count);
    }
    if (best_distance != 0x7FFFFFFF) {
        result = records[record_set].state_95;
    } else {
        result = -1;
    }
    return result;
}

