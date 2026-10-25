#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
extern M2C_UNK D_800C97F4;
extern s32 D_800D64C8[];


/* Initialize the object and set its handler and initial value. */
void initialize_reaction_object_type_21(Rec_func_80094268_arg0 *object, s32 unused, void *context) {
    initialize_object_entries((Struct800C5724 *)(object), context, D_800D64C8);
    object->unk_50.as_pm = &D_800C97F4;
    object->unk_6C.as_s16 = 0x15;
}
