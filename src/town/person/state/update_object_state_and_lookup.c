#include "common.h"
#include "shared/object_index_slots.h"
#include "records/Rec_func_80094268_arg0.h"


typedef struct S_800C4864_2 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800C4864_2;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_80 in update_object_state_and_lookup */


s16 get_cached_or_coordinate_transform_value(void *, s32);                 /* extern */
#include "town/person/object/initialize_object_entries_api.h"                /* extern */
void apply_object_setup_update(void *object, s32 callback_arg_1, s32 callback_arg_2);


/* Update the object's state, clear its indexed flag, and store the lookup result. */
void update_object_state_and_lookup(Rec_func_80094268_arg0 *object, s32 lookup_key, s32 state_value) {
    initialize_object_entries((Struct800C5724 *)(object), (s8 *)(state_value), (s32 *)(((S_800C4864_2 *)(((Rec_func_80094268_arg0 *)object)->unk_80))->unk_14));
    object_index_slots[object->unk_60].unk_00 = 0;
    object->unk_54 = &apply_object_setup_update;
    object->unk_72.as_s16 = get_cached_or_coordinate_transform_value(object, lookup_key);
}
