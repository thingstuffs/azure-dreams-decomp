#include "common.h"
#include "town/player/action_reset_data.h"
#include "town/player/object_initialization_g00546.h"
#include "shared/town_handler_entries.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"
#include "town/player.h"



/* Initialize the record from global data, clear the global flag, and set its table and counter. */
void initialize_record_with_default_handler(TownObjectRecord *record, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry(type_three_action_handler_table, record, ptr2);
    town_action_reset_byte = 0;
    record->unk_04 = &target_action_update_address;
    record->unk_0A = 8;
}
