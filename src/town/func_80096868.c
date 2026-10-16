/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

s32 scaleRandomToUnsignedHalfwordLimit();                         
void townCallTheHandlerSelectsNonzeroEntry();  
void townStoreTheValidSharedAngleInOffsetHex10(Rec_func_80094268_arg0 *);                            
void townCallTheValidSharedAngleFixedHex120000ContextCallee80094F58();                     
extern s32 D_80091990;
extern s32 D_800D0150;

void func_80093FC8(Rec_func_80094268_arg0 *object, s32 motion, s32 table_arg) {
    object->unk_3E.as_s16 = 6;
    townStoreTheValidSharedAngleInOffsetHex10(object);
    townCallTheValidSharedAngleFixedHex120000ContextCallee80094F58(motion);
    townCallTheHandlerSelectsNonzeroEntry(&D_800D0150, object, table_arg);
    object->unk_00.as_pm = &D_80091990;
    object->unk_0A.as_s16 = (s16) (scaleRandomToUnsignedHalfwordLimit(2) + 0xC);
}
