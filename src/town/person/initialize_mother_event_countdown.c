#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
extern s8 mother_event_reset_byte;
extern s32 D_800C7E70;
extern s32 mother_event_object_entries;


/* Initialize the object state, callback, countdown, and starting value. */
void initialize_mother_event_countdown(Rec_func_80094268_arg0 *object, s32 unused, s32 init_data) {
    initialize_object_entries((Struct800C5724 *)(object), (s8 *)(init_data), &mother_event_object_entries);
    mother_event_reset_byte = 0;
    object->unk_54 = &D_800C7E70;
    object->unk_6C.as_s16 = 0xA;
    object->unk_72.as_s16 = 0xC00;
}
