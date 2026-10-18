#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

void clear_entity_record_fields();                     /* extern */
typedef struct S_80098078_0 S_80098078_0;
void tick_countdown_and_initialize_target(S_80098078_0 *state, s32 value);
extern M2C_UNK D_800D0170;


/* Initialize the record, assign its handler and count, and apply the setup value. */
void initialize_record_with_handler_and_count(Rec_func_80094268_arg0 *record, s32 setup_value, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) &D_800D0170, record, ptr2);
    record->unk_04.as_pm = &tick_countdown_and_initialize_target;
    record->unk_0A.as_s16 = 0x10;
    clear_entity_record_fields(setup_value);
}
