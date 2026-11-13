#include "common.h"
#include "town/player/action_reset_data.h"
#include "shared/town_handler_entries.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"
#include "town/player/object.h"

#include "town/player/object/entity_record_fields.h"                     /* extern */
void tick_countdown_and_initialize_record(TownObjectRecord *state, s32 value, s32 mode);

/* Initialize the object, clear the global flag, and invoke the follow-up routine. */
void initialize_object_and_run_follow_up(TownObjectRecord *object, ObjectPosition *followUpArg, void *ptr2) {
    dispatch_selected_entry_if_nonzero(D_800D01A0, object, ptr2);
    town_action_reset_byte = 0;
    object->unk_04 = &tick_countdown_and_initialize_record;
    object->unk_0A = 0x15;
    clear_entity_record_fields((followUpArg));
}
