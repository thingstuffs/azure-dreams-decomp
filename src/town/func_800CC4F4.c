#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void initialize_object_entries();          /* extern */
extern M2C_UNK D_800C9864;
extern M2C_UNK D_800D64DC;


/* Initialize the object and set its handler. */
void initialize_reaction_object(Rec_func_80094268_arg0 *object, M2C_UNK unused, M2C_UNK context) {
    initialize_object_entries(object, context, &D_800D64DC);
    object->unk_50.as_pm = &D_800C9864;
}
