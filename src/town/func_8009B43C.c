#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

void func_80099754();                     /* extern */
extern s8 D_80082668;
extern M2C_UNK D_800980B4;
extern M2C_UNK D_800D0180;


/* Initialize the object's data and state, then run the setup callback. */
void func_80098B9C(Rec_func_80094268_arg0 *object, s32 setupArgument, void *ptr2) {
    func_80094984((s32 *) &D_800D0180, object, ptr2);
    object->unk_04.as_pm = &D_800980B4;
    D_80082668 = 0;
    object->unk_0A.as_s16 = 0x15;
    func_80099754(setupArgument);
    object->unk_10.as_s16 = 0;
}
