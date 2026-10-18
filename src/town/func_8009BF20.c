#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

void clear_entity_record_fields();                     /* extern */
extern s8 D_80082668;
extern M2C_UNK D_80098078;
extern M2C_UNK D_800D01E0;


/* Initialize the object and pass the setup value to the next initialization step. */
void initialize_object_with_count_four(Rec_func_80094268_arg0 *object, s32 setupValue, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) &D_800D01E0, object, ptr2);
    D_80082668 = 0;
    object->unk_04.as_pm = &D_80098078;
    object->unk_10.as_s16 = 0;
    object->unk_0A.as_s16 = 4;
    clear_entity_record_fields(setupValue);
}
