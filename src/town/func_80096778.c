#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80094984();  /* extern */
M2C_UNK func_80094C1C(Rec_func_80094268_arg0 *);                            /* extern */
M2C_UNK func_80094C74();                     /* extern */
extern M2C_UNK D_80091260;
extern M2C_UNK D_800D0090;


/* Set up the entity state and motion, then install its handler table. */
void func_80093ED8(Rec_func_80094268_arg0 *entity, M2C_UNK motion, M2C_UNK value) {
    entity->unk_3E.as_s16 = 6;
    func_80094C1C(entity);
    func_80094C74(motion);
    func_80094984(&D_800D0090, entity, value);
    entity->unk_00.as_pm = &D_80091260;
}
