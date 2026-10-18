#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void call_the_handler_selects_nonzero_entry();  /* extern */
void clear_entity_record_fields();                     /* extern */
extern s8 D_80082668;
extern M2C_UNK D_80097EC0;
extern M2C_UNK D_800D0178;


/* Initializes the object with default data and resets its state. */
void initialize_object_with_countdown_24(Rec_func_80094268_arg0 *object, s32 preparationValue, s32 initializationValue) {
    clear_entity_record_fields(preparationValue);
    call_the_handler_selects_nonzero_entry(&D_800D0178, object, initializationValue);
    object->unk_04.as_pm = &D_80097EC0;
    D_80082668 = 0;
    object->unk_0A.as_s16 = 0x18;
}
