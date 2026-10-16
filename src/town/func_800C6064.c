#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

s32 scaleRandomToUnsignedHalfwordLimit();                         /* extern */
void townInitializeObjectEntries();                /* extern */
extern M2C_UNK D_800C34EC;


/* Initializes the object, assigns its state data, and sets a value in multiples of 21. */
void func_800C37C4(Rec_func_80094268_arg0 *object, M2C_UNK unusedArg, M2C_UNK initializationArg) {
    townInitializeObjectEntries(object, initializationArg, *object->unk_7C.as_ps32);
    object->unk_50.as_pm = &D_800C34EC;
    object->unk_6C.as_s16 = (s16) (((scaleRandomToUnsignedHalfwordLimit(4) & 0xFFFF) * 0x15) + 0x15);
}
