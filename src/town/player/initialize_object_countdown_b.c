#include "common.h"
#include "shared/town_handler_entries.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/player.h"
#include "town/player/object.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"  /* extern */
#include "town/player/object/entity_record_fields.h"                     /* extern */
extern s8 town_action_reset_byte;
extern void tick_countdown_or_advance_cursor();


/* Initializes an object with default state and clears the shared flag. */
void initialize_object_with_countdown_400(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    clear_entity_record_fields((position));
    call_the_handler_selects_nonzero_entry(approach_action_handler_table, object, sprite);
    town_action_reset_byte = 0;
    object->unk_04 = &tick_countdown_or_advance_cursor;
    object->unk_0A = 0x10;
    object->unk_10 = 0x400;
}
