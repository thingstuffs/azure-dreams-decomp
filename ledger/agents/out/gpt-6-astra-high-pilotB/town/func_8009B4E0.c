#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80094984();           /* extern */
M2C_UNK func_80099754();                     /* extern */
extern M2C_UNK D_80098078;
extern M2C_UNK D_800D0170;


/* Initializes the record and invokes the follow-up routine. */
void func_80098C40(Rec_func_80094268_arg0 *record, M2C_UNK forwarded_arg) {
    func_80094984(&D_800D0170, record);
    record->unk_04.as_pm = &D_80098078;
    record->unk_0A.as_s16 = 0x10;
    func_80099754(forwarded_arg);
}
