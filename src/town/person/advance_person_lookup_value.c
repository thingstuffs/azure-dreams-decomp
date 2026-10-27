#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AB030_arg0.h"
#include "sdk/libgte.h"
#include "town/person/lookup_motion.h"



/* Advances the stored value by 0xCC and returns the helper result divided by 384. */
s32 advance_person_lookup_value(Rec_func_800AB030_arg0 *record) {
    u16 updated_value;

    updated_value = record->unk_6A + 0xCC;
    record->unk_6A = updated_value;
    return (s16) (rsin((s16) updated_value) / 384);
}
