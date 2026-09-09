#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_8009431C();        /* extern */
M2C_UNK func_80094C1C();                         /* extern */
M2C_UNK func_80094C74();                      /* extern */
M2C_UNK func_80095388();                      /* extern */
M2C_UNK func_800954F4();                      /* extern */
M2C_UNK func_80095C80();                      /* extern */
M2C_UNK func_80096810();                      /* extern */
extern u8 D_800CFCEE;


/* Update the actor record and dispatch follow-up processing when its state is nonnegative. */
void func_8009204C(s32 actor, Rec_D_800E3D7C *record, M2C_UNK context) {
    func_80096810(record);
    func_80095C80(record);
    func_80094C1C(actor);
    func_80094C74(record);
    if (D_800CFCEE != 0) {
        record->unk_14.as_s32 = 0;
        func_800954F4(record);
    } else {
        func_80095388(record);
    }
    if (record->unk_14.as_s32 >= 0) {
        func_8009431C(actor, record, context);
    }
}
