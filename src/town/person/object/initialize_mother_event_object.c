#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "town/person/object.h"

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
extern s8 mother_event_reset_byte;
extern void D_800C7EF0(void *object, void *param_1, void *param_2);
extern s32 D_800D5FA0[];


/* Initialize the object callback and clear its state values. */
void initialize_mother_event_object(Rec_func_80094268_arg0 *object, s32 unused, void *init_data) {
    initialize_object_entries((Struct800C5724 *)(object), init_data, D_800D5FA0);
    mother_event_reset_byte = 0;
    object->unk_54 = &D_800C7EF0;
    object->unk_72.as_s16 = 0;
}
