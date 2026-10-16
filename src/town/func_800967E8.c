#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

s32 scaleRandomToUnsignedHalfwordLimit();                         /* extern */
void townCallTheHandlerSelectsNonzeroEntry();  /* extern */
void townStoreTheValidSharedAngleInOffsetHex10(Rec_func_80094268_arg0 *);                            /* extern */
void townCallTheValidSharedAngleFixedHex120000ContextCallee80094F58();                     /* extern */
extern s32 D_80091528;
extern M2C_UNK D_800D0098;


/* Initialize the object state, motion, behavior data, and counter. */
void townInitializeRandomizedObjectAction(Rec_func_80094268_arg0 *object, s32 motion, s32 table_arg) {
    object->unk_3E.as_s16 = 6;
    townStoreTheValidSharedAngleInOffsetHex10(object);
    townCallTheValidSharedAngleFixedHex120000ContextCallee80094F58(motion);
    townCallTheHandlerSelectsNonzeroEntry(&D_800D0098, object, table_arg);
    object->unk_00.as_pm = &D_80091528;
    object->unk_0A.as_s16 = (s16) (scaleRandomToUnsignedHalfwordLimit(2) + 0xC);
}
