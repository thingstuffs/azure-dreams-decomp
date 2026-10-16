#include "common.h"
#include "m2c_compat.h"

s32 townApplySelectedEntryValues(void *, s32);                                /* extern */
void townWriteScriptFlagRange();   /* extern */

/* Process the request and invoke townWriteScriptFlagRange when the result is nonzero. */
s32 townProcessRequestAndNotify(void *context, s32 request) {
    s32 result;

    result = townApplySelectedEntryValues(context, request);
    if (result != 0) {
        townWriteScriptFlagRange(0xD6E, 3, 2);
    }
    return result;
}
