#include "common.h"
#include "shared/object_index_slots.h"
#include "shared/town_object.h"
#include "town/person/state.h"


typedef struct S_800C4864_2 {
    u8 pad_00[0x14];
    s32 *unk_14;
} S_800C4864_2;   /* ((TownObjectRecord *)arg0)->unk_80 in update_object_state_and_lookup */



#include "town/person/object/initialize_object_entries_api.h"                /* extern */
#include "town/person/object_setup.h"


/* Update the object's state, clear its indexed flag, and store the lookup result. */
void update_object_state_and_lookup(TownObjectRecord *object, void *lookup_key, void *state_value) {
    initialize_object_entries((Struct800C5724 *)(object), state_value, object->descriptor->entries[5]);
    object_index_slots[object->slot].unk_00 = 0;
    object->handler = &apply_object_setup_update;
    object->heading.as_s16 = get_cached_or_coordinate_transform_value(object, lookup_key);
}
