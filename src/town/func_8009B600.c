#include "common.h"
#include "shared/town_handler_entries.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void call_the_handler_selects_nonzero_entry();  /* extern */
void clear_entity_record_fields();                     /* extern */
extern M2C_UNK D_800981D4;


/* Initialize the record and set its handler and initial value. */
void initialize_record_with_handler_and_countdown_800(Rec_func_80094268_arg0 *record, s32 setup_value, s32 init_context) {
    clear_entity_record_fields(setup_value);
    call_the_handler_selects_nonzero_entry(D_800D0090, record, init_context);
    record->unk_04.as_pm = &D_800981D4;
    record->unk_10.as_s16 = 0x800;
}
