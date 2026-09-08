#include "common.h"

extern void func_800C1564(void *, void *, s32);

/* tw_sd_sq_ld_call: apply town sequence effects without additional flags. */
void func_800C15C0(void *effect_id, void *effect_flags) {
    func_800C1564(effect_id, effect_flags, 0);
}
