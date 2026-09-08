#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80094984();  /* extern */
M2C_UNK func_80094C1C(Rec_func_80094268_arg0 *);                            /* extern */
extern M2C_UNK D_80092320;
extern M2C_UNK D_800D0108;


/* Reset and initialize the record with its handler and a count of six. */
void func_800943B8(Rec_func_80094268_arg0 *record, M2C_UNK unused, M2C_UNK setup_value) {
    func_80094C1C(record);
    func_80094984(&D_800D0108, record, setup_value);
    record->unk_00.as_pm = &D_80092320;
    record->unk_0A.as_s16 = 6;
}
