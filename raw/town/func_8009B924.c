/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

void func_80099754();                     
extern s8 D_80082668;
extern s32 D_8009803C;
extern s32 D_800D01F0;

void func_80099084(Rec_func_80094268_arg0 *object, s32 followUpArg, void *ptr2) {
    func_80094984((s32 *) &D_800D01F0, object, ptr2);
    D_80082668 = 0;
    object->unk_04.as_pm = &D_8009803C;
    object->unk_0A.as_s16 = 0x10;
    func_80099754(followUpArg);
}
