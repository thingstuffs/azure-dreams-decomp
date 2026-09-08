#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800FE490.h"

M2C_UNK func_8008FCF4(Rec_D_800FE490 *);                            /* extern */


/* Initialize a record with two values and set its state flags. */
void func_8008FD48(Rec_D_800FE490 *record, s32 value_08, s32 value_0c) {
    func_8008FCF4(record);
    record->unk_08 = value_08;
    record->unk_0C = value_0c;
    record->unk_15 = 1;
    record->unk_14 = 0;
}
