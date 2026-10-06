#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void func_80094984(void *, void *, void *);           /* extern */
void func_80099754();                     /* extern */
extern s8 D_80082668;
extern M2C_UNK D_8009803C;
extern M2C_UNK D_800D01A0;


/* Initialize the object, clear the global flag, and invoke the follow-up routine. */
void func_80098FBC(Rec_func_80094268_arg0 *object, s32 followUpArg, void *ptr2) {
    func_80094984(&D_800D01A0, object, ptr2);
    D_80082668 = 0;
    object->unk_04.as_pm = &D_8009803C;
    object->unk_0A.as_s16 = 0x15;
    func_80099754(followUpArg);
}
