#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80094984();  /* extern */
M2C_UNK func_80094C1C(Rec_func_80094268_arg0 *);                            /* extern */
extern M2C_UNK D_80092A84;
extern M2C_UNK D_800D0130;


/* Set the record field to six, reset and initialize it, and assign its handler. */
void func_8009455C(Rec_func_80094268_arg0 *record, M2C_UNK unused, M2C_UNK setup_value) {
    record->unk_3E.as_s16 = 6;
    func_80094C1C(record);
    func_80094984(&D_800D0130, record, setup_value);
    record->unk_00.as_pm = &D_80092A84;
}
