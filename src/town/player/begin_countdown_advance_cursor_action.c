#include "common.h"
#include "town/player/action_reset_data.h"
#include "shared/town_handler_entries.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/player.h"
#include "town/player/position_handlers.h"
#include "town/player/object.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"  /* extern */
#include "town/player/object/entity_record_fields.h"                     /* extern */

/* Initializes an object with default state and clears the shared flag. */
void begin_countdown_advance_cursor_action(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    clear_entity_record_fields((position));
    dispatch_selected_entry_if_nonzero(approach_action_handler_table, object, sprite);
    town_action_reset_byte = 0;
    object->unk_04 = &tick_countdown_or_advance_cursor;
    object->unk_0A = 0x10;
    object->unk_10 = 0x400;
}
