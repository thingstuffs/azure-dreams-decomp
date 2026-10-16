#include "common.h"
#include "m2c_compat.h"

s32 townFindResourceIndexByKey(s32, M2C_UNK, M2C_UNK);                                /* extern */
void townMoveResourceToFront();                         /* extern */
s32 townInstallResourceDescriptorAtFront();      /* extern */

/* Find or allocate the matching entry and move it to the front. */
void townEnsureResourceAtFront(s32 kind, M2C_UNK state, M2C_UNK value) {
    s32 entry_index;

    entry_index = townFindResourceIndexByKey(kind, state, value);
    if (entry_index < 0) {
        entry_index = townInstallResourceDescriptorAtFront(kind, state, value, entry_index & 0x7FFFFFFF);
    }
    if (entry_index != 0) {
        townMoveResourceToFront(entry_index);
    }
}
