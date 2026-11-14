#include "common.h"
#include "shared/town_handler_entries.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/player.h"
#include "town/player/object.h"
#include "town/player/motion.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"  /* extern */
#include "town/player/object/entity_record_fields.h"                     /* extern */

/* Initialize the record and set its handler and initial value. */
void init_approach_record(TownObjectRecord *record, ObjectPosition *position, SpriteFrameState *init_context) {
    clear_object_velocity((position));
    dispatch_selected_entry_if_nonzero(approach_action_handler_table, record, init_context);
    record->unk_04 = &step_y_toward_fixed_target;
    record->unk_10 = 0x800;
}
