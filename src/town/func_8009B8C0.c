/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

#include "town/player/object/entity_record_fields.h"
extern s8 town_action_reset_byte;
extern s32 record_action_update_address;
extern s32 D_800D01E8;

/*
 * Selects D_800D01E8, clears town_action_reset_byte and entity motion fields, and installs
 * record_action_update_address with count 7.
 */
void init_seven_tick_record_action(Rec_func_80094268_arg0 *object, s32 motion_context, void *handler_context) {
    call_the_handler_selects_nonzero_entry((s32 *) &D_800D01E8, object, handler_context);
    town_action_reset_byte = 0;
    object->unk_04.as_pm = &record_action_update_address;
    object->unk_0A.as_s16 = 7;
    clear_entity_record_fields((struct EntityRec *)(motion_context));
}
