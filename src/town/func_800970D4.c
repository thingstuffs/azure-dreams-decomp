/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

s32 SD_Call();                     
void townCallTheHandlerSelectsNonzeroEntry();  
extern s32 D_80093524;
extern s32 D_800D0188;

void func_80094834(Rec_func_80094268_arg0 *record, s32 unused, s32 setup_value) {
    SD_Call(0x500);
    townCallTheHandlerSelectsNonzeroEntry(&D_800D0188, record, setup_value);
    record->unk_00.as_pm = &D_80093524;
    record->unk_0A.as_s16 = 0x1E;
}
