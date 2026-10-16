#include "common.h"
#include "m2c_compat.h"

void townClearSlotN3CopiesSlotN0(s32);                            /* extern */
void townClearTheGlobalStateSFifthWordCopySourceSSecond();                         /* extern */
void townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2();                         /* extern */

/* Runs the three update routines for the supplied context. */
void townRunTheThreeUpdateRoutinesContext(s32 context) {
    townClearSlotN3CopiesSlotN0(context);
    townClearTheGlobalStateSFifthWordCopySourceSSecond(context);
    townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2(context);
}
