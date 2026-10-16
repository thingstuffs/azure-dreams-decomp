#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void townClearSlotN3CopiesSlotN0(EntityRec *);                            /* extern */
extern s8 D_800CFCEB;


/* Set D_800CFCEB, initialize the record, and call townClearSlotN3CopiesSlotN0. */
void townSetGlobal800CFCEBInitializeCallCallee800954C4(EntityRec *record, s32 initial_value) {
    D_800CFCEB = 1;
    record->x.v = initial_value;
    record->unk_0C = 0;
    townClearSlotN3CopiesSlotN0(record);
}
