#include "common.h"

extern s32 townProcessTheItemIndexAvailableReportSuccess(s32 context, void *subject, s32 motion, s32 extra, void *scratch);
extern void townSelectObjectValueByHeightBand(s32 object, void *context, s32 position, s32 output);

// Clear the subject flag and run the fallback actor handler if the check fails.
void func_8009EAB0(s32 actor, void *subject, s32 motion, s32 context) {
    s32 scratch[6];

    *((s8 *)subject + 0x15) = 0;
    if (townProcessTheItemIndexAvailableReportSuccess(actor, subject, motion, context, scratch) == 0) {
        townSelectObjectValueByHeightBand(actor, subject, motion, context);
    }
}
