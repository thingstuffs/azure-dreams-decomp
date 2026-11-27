#include "common.h"
#include "shared/town_handler_entries.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"
#include "town/player/object.h"
#include "town/player.h"
#include "town/player/target_motion_g00547.h"

#include "town/player/object/entity_record_fields.h"                     /* extern */

/* Clears the object's indexed flag and updates its state and handler. */
void reset_indexed_object_and_set_handler(TownObjectRecord *object, ObjectPosition *context, void *ptr2) {
    dispatch_selected_entry_if_nonzero(target_move_direction_frames, object, ptr2);
    object_index_slots[object->index_slot].motion_id = 0;
    object->unk_0A = 0xA;
    clear_object_velocity((context));
    object->unk_04 = &move_player_toward_target;
}
