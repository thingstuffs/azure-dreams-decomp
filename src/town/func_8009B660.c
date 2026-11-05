/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/town_handler_entries.h"
#include "shared/town_object.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"
#include "town/player/object/entity_record_fields.h"
#include "town/player/object.h"
#include "town.h"
#include "town/player.h"


/*
 * Clears entity motion fields, selects approach_action_handler_table, installs D_80098244 at
 * offset 4, and stores 0x400 at offset 0x10.
 */
void init_record_target_approach(TownObjectRecord *record, ObjectPosition *position, SpriteFrameState *init_context) {
    clear_entity_record_fields((position));
    call_the_handler_selects_nonzero_entry(approach_action_handler_table, record, init_context);
    record->unk_04 = raise_record_value_to_target;
    record->unk_10 = 0x400;
}
