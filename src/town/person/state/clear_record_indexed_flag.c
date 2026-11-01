#include "common.h"
#include "town/person/state_updates.h"
#include "town/person.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/person/state.h"



/* Clear the record's indexed flag and set its state pointer. */
void clear_record_indexed_flag(TownObjectRecord *state, s32 unused_context, void *unused_state_context) {
    TownObjectRecord *record;

    record = state;
    object_index_slots[record->slot].unk_00 = 0;
    record->handler = &person_table_handler_address;
}
