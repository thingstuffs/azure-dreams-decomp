#include "town/player/position_handlers.h"
/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"

#include "town/player/object/entity_record_fields.h"
#include "town/player/object.h"
#include "town.h"
#include "town/player/motion.h"

extern s32 D_800D0198;

/*
 * Selects D_800D0198, clears the indexed object slot and entity motion fields, and installs
 * D_8009AD70 with count 0x14.
 */
void init_player_halfway_move_action(TownObjectRecord *object, ObjectPosition *context, void *ptr2) {
    dispatch_selected_entry_if_nonzero(&D_800D0198, object, ptr2);
    object_index_slots[object->unk_40].unk_00 = 0;
    object->unk_0A = 0x14;
    clear_object_velocity((context));
    object->unk_04 = move_player_halfway_to_target;
}
