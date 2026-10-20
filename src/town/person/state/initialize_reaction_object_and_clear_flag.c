#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
extern s8 D_800826B8;
void forward_reaction_object(void *object);
extern M2C_UNK D_800D6540;


/* Initialize the object, clear the shared flag, and set its callback. */
void initialize_reaction_object_and_clear_flag(Rec_func_80094268_arg0 *object, s32 unused, s32 context) {
    initialize_object_entries((Struct800C5724 *)(object), (s8 *)(context), &D_800D6540);
    D_800826B8 = 0;
    object->unk_54 = &forward_reaction_object;
}
