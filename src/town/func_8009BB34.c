/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

#include "town/player/object/entity_record_fields.h"
extern s8 town_action_reset_byte;
extern s32 target_action_update_address;
extern s32 player_event_handler_entries;

void init_four_tick_target_action(Rec_func_80094268_arg0 *object, s32 motion_context, void *handler_context) {
    call_the_handler_selects_nonzero_entry((s32 *) &player_event_handler_entries, object, handler_context);
    town_action_reset_byte = 0;
    object->unk_04.as_pm = &target_action_update_address;
    object->unk_0A.as_s16 = 4;
    clear_entity_record_fields((struct EntityRec *)(motion_context));
}
