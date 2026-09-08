#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80027328_arg0.h"

s32 func_80025080();                             /* extern */
s32 func_80026DE0();                    /* extern */
M2C_UNK func_8004B1A4();                         /* extern */


/* Release the previous resource and refresh the record from its identifier. */
void *func_80027328(Rec_func_80027328_arg0 *record, M2C_UNK resource_arg) {
    func_8004B1A4(record->unk_08);
    record->unk_04 = func_80025080(record->unk_00);
    record->unk_08 = func_80026DE0(record->unk_00, resource_arg);
    return record;
}
