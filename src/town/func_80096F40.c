/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void townCallTheHandlerSelectsNonzeroEntry();  
void townStoreTheValidSharedAngleInOffsetHex10(Rec_func_80094268_arg0 *);                            
extern s32 D_80092FF0;
extern s32 D_800D0138;

void func_800946A0(Rec_func_80094268_arg0 *record, s32 unused, s32 setup_value) {
    townStoreTheValidSharedAngleInOffsetHex10(record);
    townCallTheHandlerSelectsNonzeroEntry(&D_800D0138, record, setup_value);
    record->unk_00.as_pm = &D_80092FF0;
    record->unk_0A.as_s16 = 6;
}
