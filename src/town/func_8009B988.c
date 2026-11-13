/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "town/player/action_reset_data.h"
#include "town/player/object_initialization_g00546.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"

#include "town/player/object/entity_record_fields.h"
#include "town/player/object.h"
#include "town.h"
extern s32 D_800D01A8;

/*
 * Selects D_800D01A8, clears town_action_reset_byte and entity motion fields, and installs
 * target_action_update_address with count 60.
 */
void init_sixty_tick_target_action(TownObjectRecord *object, ObjectPosition *motion_context, void *handler_context) {
    dispatch_selected_entry_if_nonzero(&D_800D01A8, object, handler_context);
    town_action_reset_byte = 0;
    object->unk_04 = &target_action_update_address;
    object->unk_0A = 0x3C;
    clear_entity_record_fields((motion_context));
}
