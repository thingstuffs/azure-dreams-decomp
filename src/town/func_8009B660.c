/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/town_handler_entries.h"
#include "records/Rec_func_80094268_arg0.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"
#include "town/player/object/entity_record_fields.h"
extern s32 D_80098244;

/*
 * Clears entity motion fields, selects approach_action_handler_table, installs D_80098244 at
 * offset 4, and stores 0x400 at offset 0x10.
 */
void init_record_target_approach(Rec_func_80094268_arg0 *record, s32 setup_value, s32 init_context) {
    clear_entity_record_fields((struct EntityRec *)(setup_value));
    call_the_handler_selects_nonzero_entry(approach_action_handler_table, record, (void *)(init_context));
    record->unk_04.as_pm = &D_80098244;
    record->unk_10.as_s16 = 0x400;
}
