#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800165F4_arg0.h"

s32 townApplySelectedEntryValues();             /* extern */
void townSetScriptFlagBit();                         /* extern */
s32 townGetScriptFlagMask();                         /* extern */


/* Apply the record field when the query for 0x1451 succeeds, then process the record. */
void townApplyConditionalRecordValue(Rec_func_800165F4_arg0 *record, s32 context) {
    if (townGetScriptFlagMask(0x1451) != 0) {
        townSetScriptFlagBit(record->unk_18);
    }
    townApplySelectedEntryValues(record, context);
}
