#include "common.h"

extern s32 D_80017D4C;
extern s32 D_80017AAC;
extern void townCopyCallbackValueToDestination(s32 value, s32 *address);

/* Process and return the stored value. */
s32 townPrepareStoredValueBlock(void) {
    s32 *stored_value = &D_80017D4C;

    townCopyCallbackValueToDestination(*stored_value, &D_80017AAC);
    return *stored_value;
}
