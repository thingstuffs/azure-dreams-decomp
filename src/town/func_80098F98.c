#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void townClearSlotN3CopiesSlotN0(EntityRec *);                            /* extern */
extern s8 D_800CFCEA;


/* Set D_800CFCEA, initialize the record, and call townClearSlotN3CopiesSlotN0. */
void townSetGlobal800CFCEAInitializeCallCallee800954C4(EntityRec *record, s32 initial_value) {
    D_800CFCEA = 1;
    record->x.v = initial_value;
    record->unk_0C = 0;
    townClearSlotN3CopiesSlotN0(record);
}
