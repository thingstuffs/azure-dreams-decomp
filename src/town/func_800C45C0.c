#include "common.h"

extern s32 D_800D456C;
void townFindContainingRangeGroup(s32 value, s16 **range_groups);

/* Passes the value and shared data address to townFindContainingRangeGroup. */
void townPassValueAndRangeGroups(s32 value) {
    townFindContainingRangeGroup(value, &D_800D456C);
}
