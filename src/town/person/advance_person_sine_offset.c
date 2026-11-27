#include "common.h"
#include "m2c_compat.h"
#include "sdk/libgte.h"
#include "town/person/lookup_motion.h"
#include "town/person.h"



/* Advances the stored value by 0xCC and returns the helper result divided by 384. */
s32 advance_person_sine_offset(TownObjectRecord *record) {
    u16 updated_value;

    updated_value = record->sequence_step + 0xCC;
    record->sequence_step = updated_value;
    return (s16) (rsin((s16) updated_value) / 384);
}
