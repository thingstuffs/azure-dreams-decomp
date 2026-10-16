#include "common.h"
#include "m2c_compat.h"

s32 townLookupSignedIndexValue();                             /* extern */
void townSetFlaggedRecordValues();                /* extern */
extern s32 D_80100E2C[1];

/* Resolve the low-byte index, apply its value, and clear the pending state. */
void townApplyPendingIndexedValue(s32 index, M2C_UNK value) {
    s32 *pending_state;
    townSetFlaggedRecordValues(townLookupSignedIndexValue(index & 0xFF), value);
    pending_state = D_80100E2C;
    *pending_state = 0;
}
