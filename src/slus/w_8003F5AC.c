#include "engine/scene/cd_cohort_types.h"


/* Returns the stored flags with bit 2 set when D_80080AD4 is nonzero. */
s32 get_cd_flags_with_conditional_bit(void) {
    s32 flags = cd_driver_prefix[0].unk4;

    if (cd_retry_counters_pending != 0) {
        flags |= 4;
    } else {
        flags &= 0xFF;
    }
    return flags;
}
