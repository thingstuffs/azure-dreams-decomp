#include "common.h"
#include "shared/town_handler_entries.h"
#include "shared/object_index_slots.h"
#include "town/person/position.h"
#include "town/player/motion.h"
#include "town/player/object.h"
#include "town/player/record.h"

extern void dispatch_selected_entry_if_nonzero(void *entries, void *record,void *handler_param);

/* Clears the object's slot flag and initializes its state pointer and lookup result. */
void initialize_indexed_object_and_lookup_value(void *object_arg, s32 lookup_arg, s32 handler_param) {
    TownPlayerRecord *object = object_arg;

    s32 saved_lookup_arg;

    dispatch_selected_entry_if_nonzero(movement_action_handler_table, object, handler_param);
    saved_lookup_arg = lookup_arg;
    object_index_slots[object->slot].unk_00 = 0;
    object->unk_04 = &forward_player_motion_state;
    object->unk_10 = clamp_transform_coordinate_deltas(object->target_x, object->target_y,
        saved_lookup_arg);
}
