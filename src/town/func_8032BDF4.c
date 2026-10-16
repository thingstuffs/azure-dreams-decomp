#include "common.h"

extern s32 townGetScriptFlagMask(s32 flagIndex);
extern void townSetCurrentEntryScriptFlag(void);
extern void townApplySelectedEntryValues(s32 record, s32 entry_index);

/* Run the preliminary callback for condition 0x12C4, then dispatch the argument pair. */
void townDispatchAfterCondition12C4(s32 dispatch_value, s32 dispatch_option) {
    if (townGetScriptFlagMask(0x12C4) != 0) {
        townSetCurrentEntryScriptFlag();
    }
    townApplySelectedEntryValues(dispatch_value, dispatch_option);
}
