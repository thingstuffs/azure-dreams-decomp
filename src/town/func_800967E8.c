#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

s32 func_800374F4();                         /* extern */
M2C_UNK func_80094984();  /* extern */
M2C_UNK func_80094C1C(Rec_func_80094268_arg0 *);                            /* extern */
M2C_UNK func_8009503C();                     /* extern */
extern M2C_UNK D_80091528;
extern M2C_UNK D_800D0098;


/* Initialize the object state, motion, behavior data, and counter. */
void func_80093F48(Rec_func_80094268_arg0 *object, M2C_UNK motion, M2C_UNK table_arg) {
    object->unk_3E.as_s16 = 6;
    func_80094C1C(object);
    func_8009503C(motion);
    func_80094984(&D_800D0098, object, table_arg);
    object->unk_00.as_pm = &D_80091528;
    object->unk_0A.as_s16 = (s16) (func_800374F4(2) + 0xC);
}
