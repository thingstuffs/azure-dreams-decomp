/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void func_80094984();  
void func_80099754();                     
extern s32 D_80098244;
extern s32 D_800D0090;

void func_80098DC0(Rec_func_80094268_arg0 *record, s32 setup_value, s32 init_context) {
    func_80099754(setup_value);
    func_80094984(&D_800D0090, record, init_context);
    record->unk_04.as_pm = &D_80098244;
    record->unk_10.as_s16 = 0x400;
}
