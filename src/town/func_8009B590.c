#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80094984();  /* extern */
M2C_UNK func_80099754();                     /* extern */
extern s8 D_80082668;
extern M2C_UNK D_80098180;
extern M2C_UNK D_800D0090;


/* Initializes an object with default state and clears the shared flag. */
void func_80098CF0(Rec_func_80094268_arg0 *object, M2C_UNK setupParameter, M2C_UNK initializationParameter) {
    func_80099754(setupParameter);
    func_80094984(&D_800D0090, object, initializationParameter);
    D_80082668 = 0;
    object->unk_04.as_pm = &D_80098180;
    object->unk_0A.as_s16 = 0x10;
    object->unk_10.as_s16 = 0x400;
}
