#include "common.h"
#include "shared/object_index_slots.h"

typedef struct {
    s8 val;
    u8 pad[7];
} Rec8;

#include "town/person/object/initialize_object_entries_api.h"

#include "town/person/object_setup.h"
#include "town/person/motion.h"

/* Initialize the object's animation, clear its record flag, and update its facing. */
void initialize_object_animation_and_facing(TownObjectRecord *object, void *position, void *animation_state) {
    initialize_object_entries(object, animation_state, object->descriptor->entries[5]);
    object_index_slots[object->slot].unk_00 = 0;
    object->handler = (void *)apply_object_setup_update;
    object->heading.as_s16 = clamp_transform_coordinate_deltas(
        object->target_x,
        object->target_y,
        position);
}
