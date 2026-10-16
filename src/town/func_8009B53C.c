#include "common.h"

extern void townInitializeRecordWithHandlerAndCount(s32 record, s32 setup_value, s32 context_value);
extern s8 D_80082668;

/* Forward the values to townInitializeRecordWithHandlerAndCount and clear D_80082668. */
void townInitializeRecordAndClearSharedFlag(s32 primary_value, s32 secondary_value, s32 context_value) {
    townInitializeRecordWithHandlerAndCount(primary_value, secondary_value, context_value);
    D_80082668 = 0;
}
