/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

s32 SD_Call();                     
void func_80094984();  
extern s32 D_80092698;
extern s32 D_800D0120;

void func_800944BC(Rec_func_80094268_arg0 *record, s32 unused, s32 setup_value) {
    SD_Call(0x511);
    func_80094984(&D_800D0120, record, setup_value);
    record->unk_00.as_pm = &D_80092698;
    record->unk_0A.as_s16 = 6;
}
