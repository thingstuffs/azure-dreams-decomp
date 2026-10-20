#include "common.h"
#include "shared/town_handler_entries.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

#include "town/player/object/entity_record_fields.h"                     /* extern */
typedef struct S_80098078_0 S_80098078_0;
void tick_countdown_and_initialize_target(S_80098078_0 *state, s32 value);


/* Initialize the record, assign its handler and count, and apply the setup value. */
void initialize_record_with_handler_and_count(Rec_func_80094268_arg0 *record, s32 setup_value, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) D_800D0170, record, ptr2);
    record->unk_04.as_pm = &tick_countdown_and_initialize_target;
    record->unk_0A.as_s16 = 0x10;
    clear_entity_record_fields((struct EntityRec *)(setup_value));
}
