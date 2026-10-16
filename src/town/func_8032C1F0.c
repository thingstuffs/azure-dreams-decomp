#include "common.h"

extern void townApplySelectedEntryValues(s32 record, s32 entry_index);
extern void townSetCurrentEntryScriptFlag(void);
extern s32 townGetLinkedRecordField2D60(void);

/* Process the request after checking the threshold of 25. */
void func_800169F0(s32 request, s32 context) {
    if (townGetLinkedRecordField2D60() >= 0x19) {
        townSetCurrentEntryScriptFlag();
    }
    townApplySelectedEntryValues(request, context);
}
