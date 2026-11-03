#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "town/player/motion.h"
#include "town/player/record.h"

/* extern */



void initialize_target_and_handler_table(TownPlayerRecord *, ObjectPosition *);
/* Clear the indexed table entry and call initialize_target_and_handler_table. */
void clear_player_motion_entry(TownPlayerRecord *object, ObjectPosition *position) {
    object_index_slots[object->slot].unk_00 = 0;
    initialize_target_and_handler_table(object, position);
}
