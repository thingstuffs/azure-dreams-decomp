#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
extern void D_800CD70C();
extern s32 D_800D72AC[];


/* Initialize the object and set its data pointer and initial field values. */
void initialize_object_and_data_pointer(Rec_func_80094268_arg0 *object, s32 unused, s32 init_value) {
    initialize_object_entries((Struct800C5724 *)(object), (s8 *)(init_value), &D_800D72AC);
    object->unk_50.as_pm = &D_800CD70C;
    object->unk_84.as_s16 = 0x50;
    object->unk_6C.as_s16 = 0xD2;
}
