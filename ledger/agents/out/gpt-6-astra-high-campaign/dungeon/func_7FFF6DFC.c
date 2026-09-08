#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80094984();
M2C_UNK func_80094C1C();
extern M2C_UNK D_80092A84;
extern M2C_UNK D_800D0130;


/* Set the object's unk_3E to six and initialize its state data. */
void func_8009455C(Rec_func_80094268_arg0 *object, M2C_UNK setup_arg, M2C_UNK context, M2C_UNK setup_extra) {
    object->unk_3E.as_s16 = 6;
    func_80094C1C(object, setup_arg, context, setup_extra);
    func_80094984(&D_800D0130, object, context);
    object->unk_00.as_pm = &D_80092A84;
}
