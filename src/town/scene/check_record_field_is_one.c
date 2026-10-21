#include "shared/town_event_state.h"
#include "common.h"
#include "m2c_compat.h"



/* Checks whether the current record's unk_04 field equals one. */
s32 check_record_field_0x04_is_one(void) {
    return town_event_state->unk_04 == 1;
}
