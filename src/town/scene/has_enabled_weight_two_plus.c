#include "common.h"
#include "town/player.h"
#include "town/scene.h"

/* Returns whether sum_enabled_record_weights reports a value of at least two. */
s32 has_enabled_weight_two_plus(void) {
    return sum_enabled_record_weights() >= 2;
}
