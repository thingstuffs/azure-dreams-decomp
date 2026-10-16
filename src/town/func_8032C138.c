#include "common.h"

extern s32 townApplySelectedEntryValues();
extern void townSetCurrentEntryScriptFlag();
extern s32 townGetLinkedRecordField2D60();

/* Process the request after checking the threshold of 20. */
void townProcessRequestAfterThreshold20(s32 request, s32 context) {
    if (townGetLinkedRecordField2D60() >= 0x14) {
        townSetCurrentEntryScriptFlag();
    }
    townApplySelectedEntryValues(request, context);
}
