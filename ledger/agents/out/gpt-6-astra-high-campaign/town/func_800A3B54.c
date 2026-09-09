#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80100B70.h"

M2C_UNK func_800A17CC(Rec_D_80100B70 *, s32);                            /* extern */


/* Decrease the value with a floor of four, advance the cyclic counter, and update the record. */
void func_800A12B4(Rec_D_80100B70 *record, s32 value) {
    u16 reduced_value;

    reduced_value = record->unk_12 - 4;
    record->unk_12 = reduced_value;
    if ((s16) reduced_value < 4) {
        record->unk_12 = 4U;
    }
    record->unk_6E = (u16) ((record->unk_6E + 1) & 0x7F);
    func_800A17CC(record, value);
}
