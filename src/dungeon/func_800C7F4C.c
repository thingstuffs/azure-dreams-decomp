#include "modules/trap_effects_candidate.h"
#include "common.h"

extern s32 try_apply_effect_four_by_chance(void *actor, s32 chance, s32 action);            /* extern */


/* Apply the global-mode mask to the target with a fixed value of 0x10. */
void apply_mode_selected_trap_mask(target)
s32 target;
{
    s32 mode_mask;

    mode_mask = 0x40;
    if (D_800E3D40 != 0) {
        mode_mask = 0x400;
    }
    try_apply_effect_four_by_chance(target, mode_mask, 0x10);
}
