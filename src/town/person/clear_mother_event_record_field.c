#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/person.h"

/* Clears the record's unk_94 field. */
void clear_mother_event_record_field(TownObjectRecord *record, ObjectPosition *unused_position, SpriteFrameState *unused_update_arg) {
    record->state_index = 0;
}
