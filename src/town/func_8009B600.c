#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void townCallTheHandlerSelectsNonzeroEntry();  /* extern */
void townClearEntityRecordFields();                     /* extern */
extern M2C_UNK D_800981D4;
extern M2C_UNK D_800D0090;


/* Initialize the record and set its handler and initial value. */
void townInitializeRecordWithHandlerAndCountdown800(Rec_func_80094268_arg0 *record, s32 setup_value, s32 init_context) {
    townClearEntityRecordFields(setup_value);
    townCallTheHandlerSelectsNonzeroEntry(&D_800D0090, record, init_context);
    record->unk_04.as_pm = &D_800981D4;
    record->unk_10.as_s16 = 0x800;
}
