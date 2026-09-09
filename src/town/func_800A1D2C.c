#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8009EE9C_arg0.h"

M2C_UNK func_80033D08(Rec_func_8009EE9C_arg0 *, s32);                            /* extern */
extern M2C_UNK D_8009F2A8;


/* Call func_80033D08 and set the record handler. */
void func_8009F48C(Rec_func_8009EE9C_arg0 *record, s32 value) {
    func_80033D08(record, value);
    record->unk_50.as_pm = &D_8009F2A8;
}
