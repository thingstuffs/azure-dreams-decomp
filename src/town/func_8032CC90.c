#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800165F4_arg0.h"

s32 townApplySelectedEntryValues();             /* extern */
void townSetScriptFlagBit();                         /* extern */
s32 townGetLinkedRecordField2D60();                                /* extern */


/* Conditionally process the record ID before passing the record to townApplySelectedEntryValues. */
void townApplyRecordValueWhenEnabled(Rec_func_800165F4_arg0 *record, s32 handler_context) {
    if (townGetLinkedRecordField2D60() != 0) {
        townSetScriptFlagBit(record->unk_18);
    }
    townApplySelectedEntryValues(record, handler_context);
}
