/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "town/player/object_initialization_g00546.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

#include "town/player/object/entity_record_fields.h"
extern s8 town_action_reset_byte;
extern s32 D_800D01A8;

/*
 * Selects D_800D01A8, clears town_action_reset_byte and entity motion fields, and installs
 * target_action_update_address with count 60.
 */
void init_sixty_tick_target_action(Rec_func_80094268_arg0 *object, s32 motion_context, void *handler_context) {
    call_the_handler_selects_nonzero_entry((s32 *) &D_800D01A8, object, handler_context);
    town_action_reset_byte = 0;
    object->unk_04.as_pm = &target_action_update_address;
    object->unk_0A.as_s16 = 0x3C;
    clear_entity_record_fields((struct EntityRec *)(motion_context));
}
