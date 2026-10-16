#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

s32 townHandleQueryPositionAfterSubtractingGlobalZOffset(EntityRec *);                                /* extern */
void townSetTheClearSecondaryRefreshGlobalFlagSet();                 /* extern */
extern s32 D_800FE5D4;


/* Update the record to the computed upper bound when the global state permits. */
void townUpdateTheComputedUpperBoundGlobalStatePermits(EntityRec *record) {
    s32 upper_bound;

    if (D_800FE5D4 < 0) {
        upper_bound = (townHandleQueryPositionAfterSubtractingGlobalZOffset(record) << 0x10) - 1;
        if (upper_bound >= record->z.v) {
            townSetTheClearSecondaryRefreshGlobalFlagSet(record, upper_bound);
        }
    }
}
