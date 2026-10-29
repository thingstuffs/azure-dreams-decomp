#include "common.h"
#include "town/player/object_initialization_g00546.h"
#include "shared/town_handler_entries.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"
#include "town/player.h"

extern s8 town_action_reset_byte;


/* Initialize the record from global data, clear the global flag, and set its table and counter. */
void initialize_record_with_default_handler(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) type_three_action_handler_table, record, ptr2);
    town_action_reset_byte = 0;
    record->unk_04.as_pm = &target_action_update_address;
    record->unk_0A.as_s16 = 8;
}
