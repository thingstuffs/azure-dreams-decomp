#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void call_the_handler_selects_nonzero_entry();  /* extern */
void clear_entity_record_fields();                     /* extern */
extern M2C_UNK D_80097DE8;
extern s32 D_800D0178;


/* Initializes the object, assigns its handler table, and clears two global flags. */
void initialize_indexed_object_and_clear_flags(Rec_func_80094268_arg0 *object, s32 setupValue, s32 initializationValue) {
    clear_entity_record_fields(setupValue);
    call_the_handler_selects_nonzero_entry(&D_800D0178, object, initializationValue);
    object->unk_04.as_pm = &D_80097DE8;
    D_80082660[1].unk_00 = 0;
    D_80082660[1].unk_01 = 0;
}
