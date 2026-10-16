#include "common.h"

s32 townSumEnabledRecordWeights();                                /* extern */

/* Returns whether townSumEnabledRecordWeights reports a value of at least two. */
s32 townCheckStateAtLeastTwo(void) {
    return townSumEnabledRecordWeights() >= 2;
}
