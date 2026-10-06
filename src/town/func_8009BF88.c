#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void func_80094984(void *, void *, void *);           /* extern */
void func_80099754();                     /* extern */
extern s8 D_80082668;
extern M2C_UNK D_80098078;
extern M2C_UNK D_800D01E0;


/* Initialize the object's state and run the follow-up setup. */
void func_800996E8(Rec_func_80094268_arg0 *object, s32 setupContext, void *ptr2) {
    func_80094984(&D_800D01E0, object, ptr2);
    D_80082668 = 0;
    object->unk_10.as_s16 = 0x800;
    object->unk_04.as_pm = &D_80098078;
    object->unk_0A.as_s16 = 4;
    func_80099754(setupContext);
}
