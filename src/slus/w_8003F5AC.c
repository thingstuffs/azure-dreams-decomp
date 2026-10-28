#include "engine/scene/cd_cohort_types.h"
#include "slus.h"


/*
 * Returns the stored CD flags with bit 2 set while retries are pending; otherwise masks the flags
 * to eight bits.
 */
s32 get_cd_flags_with_conditional_bit(void) {
    s32 flags = cd_driver_prefix[0].unk4;

    if (cd_retry_counters_pending != 0) {
        flags |= 4;
    } else {
        flags &= 0xFF;
    }
    return flags;
}
