#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800165F4_arg0.h"

s32 townCheckProgressAgainstCallback();                                /* extern */
s32 townProcessCheckedEntry();             /* extern */
void townSetScriptFlagBit();                         /* extern */
void townClearScriptFlagBit();                     /* extern */


/* Process flag 0xD52, conditionally select the object value, and forward the request. */
void townProcessFlagAndForwardRequest(Rec_func_800165F4_arg0 *object, s32 request_data) {
    townClearScriptFlagBit(0xD52);
    if (townCheckProgressAgainstCallback() != 0) {
        townSetScriptFlagBit(object->unk_18);
    }
    townProcessCheckedEntry(object, request_data);
}
