#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800165F4_arg0.h"

s32 townApplySelectedEntryValues();             /* extern */
void townSetScriptFlagBit();                         /* extern */
s32 townGetScriptFlagMask();                         /* extern */


/* Applies the object's stored value when either condition is active, then forwards the call. */
void townApplyRecordValueForEitherFlag(Rec_func_800165F4_arg0 *object, s32 context) {
    if ((townGetScriptFlagMask(0x1388) != 0) || (townGetScriptFlagMask(0x138A) != 0)) {
        townSetScriptFlagBit(object->unk_18);
    }
    townApplySelectedEntryValues(object, context);
}
