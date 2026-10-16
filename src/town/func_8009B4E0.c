#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

void townClearEntityRecordFields();                     /* extern */
extern M2C_UNK D_80098078;
extern M2C_UNK D_800D0170;


/* Initialize the record, assign its handler and count, and apply the setup value. */
void townInitializeRecordWithHandlerAndCount(Rec_func_80094268_arg0 *record, s32 setup_value, void *ptr2) {
    townCallTheHandlerSelectsNonzeroEntry((s32 *) &D_800D0170, record, ptr2);
    record->unk_04.as_pm = &D_80098078;
    record->unk_0A.as_s16 = 0x10;
    townClearEntityRecordFields(setup_value);
}
