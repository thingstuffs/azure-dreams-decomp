#include "common.h"

s32 sum_enabled_record_weights(void);                                /* extern */

/* Returns whether sum_enabled_record_weights reports a value of at least two. */
s32 check_state_at_least_two(void) {
    return sum_enabled_record_weights() >= 2;
}
