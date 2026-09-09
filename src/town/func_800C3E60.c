#include "common.h"

extern void tw_sd_sq_ld_call_sub(void *, void *, s32);

/* tw_sd_sq_ld_call: apply town sequence effects without additional flags. */
void tw_sd_sq_ld_call(void *effect_id, void *effect_flags) {
    tw_sd_sq_ld_call_sub(effect_id, effect_flags, 0);
}
