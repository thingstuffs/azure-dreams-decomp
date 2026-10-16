#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void townCallTheHandlerSelectsNonzeroEntry();  /* extern */
void townStoreTheValidSharedAngleInOffsetHex10(Rec_func_80094268_arg0 *);                            /* extern */
extern M2C_UNK D_80092320;
extern M2C_UNK D_800D0108;


/* Reset and initialize the record with its handler and a count of six. */
void func_800943B8(Rec_func_80094268_arg0 *record, s32 unused, s32 setup_value) {
    townStoreTheValidSharedAngleInOffsetHex10(record);
    townCallTheHandlerSelectsNonzeroEntry(&D_800D0108, record, setup_value);
    record->unk_00.as_pm = &D_80092320;
    record->unk_0A.as_s16 = 6;
}
