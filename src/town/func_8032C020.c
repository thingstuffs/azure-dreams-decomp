#include "common.h"

extern s32 townGetLinkedRecordField2D60(void);
extern s32 townSetCurrentEntryScriptFlag();
extern s32 townApplySelectedEntryValues();

/* Run the preliminary callback at a count of ten or more, then dispatch the argument pair. */
void func_80016820(s32 dispatch_value, s32 dispatch_option) {
    if (townGetLinkedRecordField2D60() >= 10) {
        townSetCurrentEntryScriptFlag();
    }
    townApplySelectedEntryValues(dispatch_value, dispatch_option);
}
