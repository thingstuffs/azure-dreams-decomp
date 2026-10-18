#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void call_the_handler_selects_nonzero_entry();  /* extern */
void clear_entity_record_fields();                     /* extern */
extern s8 D_80082668;
extern M2C_UNK D_80098180;
extern M2C_UNK D_800D0090;


/* Initializes an object with default state and clears the shared flag. */
void initialize_object_with_countdown_400(Rec_func_80094268_arg0 *object, s32 setupParameter, s32 initializationParameter) {
    clear_entity_record_fields(setupParameter);
    call_the_handler_selects_nonzero_entry(&D_800D0090, object, initializationParameter);
    D_80082668 = 0;
    object->unk_04.as_pm = &D_80098180;
    object->unk_0A.as_s16 = 0x10;
    object->unk_10.as_s16 = 0x400;
}
