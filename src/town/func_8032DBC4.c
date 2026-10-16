#include "common.h"
#include "m2c_compat.h"

s32 townApplySelectedEntryValues();                /* extern */
void townSetCurrentEntryScriptFlag();                            /* extern */
void townSetScriptFlagBit();                     /* extern */
s32 townGetLinkedRecordField2D60();                                /* extern */

/* Conditionally reset the subsystem, select 0xD7F, and forward the request. */
void townResetAndDispatchRequest(s32 request, s32 request_data) {
    if (townGetLinkedRecordField2D60() >= 5) {
        townSetCurrentEntryScriptFlag();
    }
    townSetScriptFlagBit(0xD7F);
    townApplySelectedEntryValues(request, request_data);
}
