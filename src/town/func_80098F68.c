#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

M2C_UNK func_800954C4(EntityRec *);                            /* extern */
extern s8 D_800CFCEB;


/* Set D_800CFCEB, initialize the record, and call func_800954C4. */
void func_800966C8(EntityRec *record, s32 initial_value) {
    D_800CFCEB = 1;
    record->x.v = initial_value;
    record->unk_0C = 0;
    func_800954C4(record);
}
