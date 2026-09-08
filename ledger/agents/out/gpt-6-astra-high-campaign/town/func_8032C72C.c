#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800165F4_arg0.h"

M2C_UNK func_80019B54();             /* extern */
M2C_UNK func_8001ACE8();                         /* extern */
s32 func_8001ADE0();                         /* extern */


/* Apply the record field when the query for 0x1451 succeeds, then process the record. */
void func_80016F2C(Rec_func_800165F4_arg0 *record, M2C_UNK context) {
    if (func_8001ADE0(0x1451) != 0) {
        func_8001ACE8(record->unk_18);
    }
    func_80019B54(record, context);
}
