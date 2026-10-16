/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

void townClearEntityRecordFields();                     
extern s8 D_80082668;
extern s32 D_80098078;
extern s32 D_800D01A8;

void func_800990E8(Rec_func_80094268_arg0 *object, s32 followUpArg, void *ptr2) {
    townCallTheHandlerSelectsNonzeroEntry((s32 *) &D_800D01A8, object, ptr2);
    D_80082668 = 0;
    object->unk_04.as_pm = &D_80098078;
    object->unk_0A.as_s16 = 0x3C;
    townClearEntityRecordFields(followUpArg);
}
