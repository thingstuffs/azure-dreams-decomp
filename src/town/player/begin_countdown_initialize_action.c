#include "town/player/position_handlers.h"
#include "common.h"
#include "town/player/action_reset_data.h"
#include "shared/town_object.h"
#include "town/player.h"
#include "town/player/object.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"  /* extern */
#include "town/player/object/entity_record_fields.h"                     /* extern */
extern s32 D_800D0178;

/* Initializes the object with default data and resets its state. */
void begin_countdown_initialize_action(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *initializationValue) {
    clear_object_velocity((position));
    dispatch_selected_entry_if_nonzero(&D_800D0178, object, initializationValue);
    object->unk_04 = &tick_countdown_and_initialize_object;
    town_action_reset_byte = 0;
    object->unk_0A = 0x18;
}
