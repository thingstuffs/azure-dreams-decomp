#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80094984();           /* extern */
M2C_UNK func_80099754();                     /* extern */
extern u8 D_80082660;
extern M2C_UNK D_80098078;
extern M2C_UNK D_800D0120;


/* Clears the object's indexed flag and resets its state before processing the context. */
void func_8009914C(Rec_func_80094268_arg0 *object, M2C_UNK context) {
    func_80094984(&D_800D0120, object);
    *((object->unk_40 * 8) + &D_80082660) = 0;
    object->unk_04.as_pm = &D_80098078;
    object->unk_0A.as_s16 = 6;
    func_80099754(context);
}
