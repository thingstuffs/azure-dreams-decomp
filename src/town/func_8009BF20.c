#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80094984();           /* extern */
M2C_UNK func_80099754();                     /* extern */
extern s8 D_80082668;
extern M2C_UNK D_80098078;
extern M2C_UNK D_800D01E0;


/* Initialize the object and pass the setup value to the next initialization step. */
void func_80099680(Rec_func_80094268_arg0 *object, M2C_UNK setupValue) {
    func_80094984(&D_800D01E0, object);
    D_80082668 = 0;
    object->unk_04.as_pm = &D_80098078;
    object->unk_10.as_s16 = 0;
    object->unk_0A.as_s16 = 4;
    func_80099754(setupValue);
}
