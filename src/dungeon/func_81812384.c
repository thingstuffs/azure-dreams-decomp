#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80027328_arg0.h"

s32 func_80026E30();                             /* extern */
s32 func_80027008();               /* extern */
M2C_UNK func_8004B1A4();                         /* extern */


/* Release the previous resource and rebuild it using the refreshed record value. */
void *func_80027384(Rec_func_80027328_arg0 *record, M2C_UNK resource_arg) {
    s32 resource_value;

    func_8004B1A4(record->unk_08);
    resource_value = func_80026E30(record->unk_00);
    record->unk_04 = resource_value;
    record->unk_08 = func_80027008(record->unk_00, resource_arg, resource_value);
    return record;
}
