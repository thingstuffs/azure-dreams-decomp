#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void townCallTheHandlerSelectsNonzeroEntry();  /* extern */
void townClearEntityRecordFields();                     /* extern */
extern s8 D_80082668;
extern M2C_UNK D_80097EC0;
extern M2C_UNK D_800D0178;


/* Initializes the object with default data and resets its state. */
void townInitializeObjectWithCountdown24(Rec_func_80094268_arg0 *object, s32 preparationValue, s32 initializationValue) {
    townClearEntityRecordFields(preparationValue);
    townCallTheHandlerSelectsNonzeroEntry(&D_800D0178, object, initializationValue);
    object->unk_04.as_pm = &D_80097EC0;
    D_80082668 = 0;
    object->unk_0A.as_s16 = 0x18;
}
