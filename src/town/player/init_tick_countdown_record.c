#include "common.h"
#include "town/player/action_initializers.h"
#include "shared/town_handler_entries.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"
#include "town/player.h"
#include "town/player/object.h"

#include "town/player/object/entity_record_fields.h"                     /* extern */

/* Initialize the record, assign its handler and count, and apply the setup value. */
void init_tick_countdown_record(TownObjectRecord *record, ObjectPosition *position, void *ptr2) {
    dispatch_selected_entry_if_nonzero(D_800D0170, record, ptr2);
    record->unk_04 = &tick_countdown_and_initialize_target;
    record->unk_0A = 0x10;
    clear_object_velocity(position);
}
