#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void func_8009431C();        /* extern */
void func_80094C1C();                         /* extern */
void func_80094C74();                      /* extern */
void func_80095388();                      /* extern */
void func_800954F4();                      /* extern */
void func_80095C80();                      /* extern */
void func_80096810();                      /* extern */
extern u8 D_800CFCEE;


/* Update the actor record and dispatch follow-up processing when its state is nonnegative. */
void func_8009204C(s32 actor, EntityRec *record, M2C_UNK context) {
    func_80096810(record);
    func_80095C80(record);
    func_80094C1C(actor);
    func_80094C74(record);
    if (D_800CFCEE != 0) {
        record->flags14 = 0;
        func_800954F4(record);
    } else {
        func_80095388(record);
    }
    if (record->flags14 >= 0) {
        func_8009431C(actor, record, context);
    }
}
