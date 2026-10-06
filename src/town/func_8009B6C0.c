#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void func_80094984(void *, void *, void *);           /* extern */
extern s8 D_80082668;
extern M2C_UNK D_80098078;
extern M2C_UNK D_800D00A0;


/* Initialize the record from global data, clear the global flag, and set its table and counter. */
void func_80098E20(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2) {
    func_80094984(&D_800D00A0, record, ptr2);
    D_80082668 = 0;
    record->unk_04.as_pm = &D_80098078;
    record->unk_0A.as_s16 = 8;
}
