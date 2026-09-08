#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800165F4_arg0.h"

M2C_UNK func_80019B54();             /* extern */
M2C_UNK func_8001ACE8();                         /* extern */
s32 func_8001B0C8();                                /* extern */


/* Conditionally process the record ID before passing the record to func_80019B54. */
void func_80017490(Rec_func_800165F4_arg0 *record, M2C_UNK handler_context) {
    if (func_8001B0C8() != 0) {
        func_8001ACE8(record->unk_18);
    }
    func_80019B54(record, handler_context);
}
