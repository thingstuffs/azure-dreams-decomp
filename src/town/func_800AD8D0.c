#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AB030_arg0.h"

s32 func_800644B8();                             /* extern */


/* Advances the stored value by 0xCC and returns the helper result divided by 384. */
s16 func_800AB030(Rec_func_800AB030_arg0 *record) {
    u16 updated_value;

    updated_value = record->unk_6A + 0xCC;
    record->unk_6A = updated_value;
    return (s16) (func_800644B8((s16) updated_value) / 384);
}
