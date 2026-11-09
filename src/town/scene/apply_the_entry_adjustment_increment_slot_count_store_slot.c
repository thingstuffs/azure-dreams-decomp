#include "shared/game_work.h"
#include "town/scene/collision.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
/*
 * For an unflagged entry, subtracts its adjustment from the current value and clears the pending
 * delta. Increments the selected slot byte and stores the entry value in the indexed word table.
 */
void apply_the_entry_adjustment_increment_slot_count_store_slot(ColliderView *state_base, ObjectPosition *value_record, CollisionScratch *entry)
{
    int adjusted_value;
    if (entry->face_x == 0) {
        adjusted_value = value_record->x.v - entry->x_near;
        value_record->velocity_x = 0;
        value_record->x.v = adjusted_value;
    }
    state_base->pending_flags[entry->axis_x] = (u8)(state_base->pending_flags[entry->axis_x] + 1);
    state_base->slots[entry->axis_x] = entry->other;
}
