#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
extern M2C_UNK D_800C9864;
extern s32 D_800D64DC[];


/* Initialize the object and set its handler. */
void initialize_reaction_object(Rec_func_80094268_arg0 *object, s32 unused, s32 context) {
    initialize_object_entries((Struct800C5724 *)(object), (s8 *)(context), &D_800D64DC);
    object->unk_50.as_pm = &D_800C9864;
}
