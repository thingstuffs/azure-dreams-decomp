#include "common.h"
#include "shared/town_handler_entries.h"
#include "shared/object_index_slots.h"
#include "town/person/position.h"
#include "town/player/motion.h"
#include "town/player/object.h"
#include "town/player/record.h"

extern void dispatch_selected_entry_if_nonzero(void *entries, void *record,void *handler_param);

/* Clears the object's slot flag and initializes its state pointer and lookup result. */
void initialize_indexed_object_and_lookup_value(TownPlayerRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    dispatch_selected_entry_if_nonzero(movement_action_handler_table, object, sprite);
    object_index_slots[object->slot].motion_id = 0;
    object->sub_callback = &forward_player_motion_state;
    object->facing = clamp_transform_coordinate_deltas(object->target_x, object->target_y, position);
}
