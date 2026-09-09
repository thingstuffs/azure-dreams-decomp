#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008F074_arg0.h"

M2C_UNK func_8008F01C(Rec_func_8008F074_arg0 *, s32, s32);                            /* extern */


/* Configure the record and set its mode to 1. */
void func_8008F074(Rec_func_8008F074_arg0 *record, s32 setup_value, s32 setup_param) {
    func_8008F01C(record, setup_value, setup_param);
    record->unk_14 = 1;
}
