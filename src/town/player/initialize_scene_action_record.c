#include "common.h"
#include "town/player/state_update_g00548.h"
#include "town/player/action_initializers.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"
#include "town/player.h"
#include "town/player/object.h"

/* Initialize the record, set its first pointer to update_entity_and_handle_flagged_action, and store code 0x54. */
void initialize_scene_action_record(TownObjectRecord *record, void *ptr, void *ptr2) {
    dispatch_selected_entry_if_nonzero((s32 *) &town_scene_record_handlers, record, ptr2);
    record->unk_00 = &update_entity_and_handle_flagged_action;
    record->unk_0A = 0x54;
}
