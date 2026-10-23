#include "common.h"
#include "shared/town_handler_entries.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"  /* extern */
#include "town/player/object/entity_record_fields.h"                     /* extern */
extern s32 D_800981D4();


/* Initialize the record and set its handler and initial value. */
void initialize_record_with_handler_and_countdown_800(Rec_func_80094268_arg0 *record, s32 setup_value, s32 init_context) {
    clear_entity_record_fields((struct EntityRec *)(setup_value));
    call_the_handler_selects_nonzero_entry(approach_action_handler_table, record, (void *)(init_context));
    record->unk_04.as_pm = &D_800981D4;
    record->unk_10.as_s16 = 0x800;
}
