#include "common.h"
#include "m2c_compat.h"

s32 townGetLowerProbeResultSamplingXOffsetDisplacementExceedsLimit(s32 *);                           /* extern */
s32 townHandleQueriesLargeOffsetReturnsLargerOriginalShiftedResult();                           /* extern */
void townSetGlobal800CFCEBInitializeCallCallee800954C4();                  /* extern */
void townSetGlobal800CFCEAInitializeCallCallee800954C4();                  /* extern */
extern s32 D_800FE5CC;

/* Applies fixed-point boundary corrections according to D_800FE5CC. */
void townApplyFixedPointBoundaryCorrectionsAccordingGlobal800FE5CC(s32 *value) {
    s32 upper_bound;
    s32 neutral_upper_bound;
    s32 lower_bound;

    if (D_800FE5CC > 0) {
        upper_bound = townGetLowerProbeResultSamplingXOffsetDisplacementExceedsLimit(value) << 0x10;
        if (*value >= upper_bound) {
            townSetGlobal800CFCEBInitializeCallCallee800954C4(value, upper_bound);
            return;
        }
    } else {
        if (D_800FE5CC >= 0) {
            neutral_upper_bound = townGetLowerProbeResultSamplingXOffsetDisplacementExceedsLimit(value) << 0x10;
            if (*value >= neutral_upper_bound) {
                townSetGlobal800CFCEBInitializeCallCallee800954C4(value, neutral_upper_bound);
            }
        }
        lower_bound = (townHandleQueriesLargeOffsetReturnsLargerOriginalShiftedResult(value) << 0x10) - 1;
        if (lower_bound >= *value) {
            townSetGlobal800CFCEAInitializeCallCallee800954C4(value, lower_bound);
        }
    }
}
