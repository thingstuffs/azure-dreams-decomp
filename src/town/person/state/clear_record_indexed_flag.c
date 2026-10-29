#include "common.h"
#include "town/person/state_updates.h"
#include "town/person.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "town/person/state.h"



/* Clear the record's indexed flag and set its state pointer. */
void clear_record_indexed_flag(void *state, s32 unused_context, void *unused_state_context) {
    Rec_func_80094268_arg0 *record;

    record = state;
    object_index_slots[record->unk_60].unk_00 = 0;
    record->unk_54 = &person_table_handler_address;
}
