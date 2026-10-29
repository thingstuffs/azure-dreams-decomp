#include "common.h"
#include "town/player/action_initializers.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"
#include "town/player.h"
#include "town/player/object.h"
extern u8 town_scene_record_handlers[];


/* Initialize the record, set its first pointer to update_entity_and_handle_flagged_action, and store code 0x54. */
void initialize_scene_action_record(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) &town_scene_record_handlers, record, ptr2);
    record->unk_00.as_pm = &update_entity_and_handle_flagged_action;
    record->unk_0A.as_s16 = 0x54;
}
