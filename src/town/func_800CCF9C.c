#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void initialize_object_entries();          /* extern */
extern s8 D_800826B8;
extern M2C_UNK D_800CA114;
extern M2C_UNK D_800D6540;


/* Initialize the object, clear the shared flag, and set its callback. */
void initialize_reaction_object_and_clear_flag(Rec_func_80094268_arg0 *object, M2C_UNK unused, M2C_UNK context) {
    initialize_object_entries(object, context, &D_800D6540);
    D_800826B8 = 0;
    object->unk_54 = &D_800CA114;
}
