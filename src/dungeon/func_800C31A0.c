#include "common.h"

extern s32 roll_chance_and_apply_effect_four(void *, s16, s16);
extern void adjust_source_value_and_finalize(void *, const u8 *);
extern void wrap_position_and_set_state_value(s32);
extern u8 D_800E19E8[];
extern u8 D_800E1A01[];
extern s32 D_800DCF18;

/* Apply the chance-based status and select its success or failure message. */
s32 try_apply_effect_four_by_chance(void *actor, s32 chance, s32 action)
{
    if (roll_chance_and_apply_effect_four(actor, (s16)chance, (s16)action)) {
        adjust_source_value_and_finalize(actor, D_800E19E8);
        if (((u8 *)actor)[0x13] == 0) {
            wrap_position_and_set_state_value(D_800DCF18);
        }
        return 1;
    }
    adjust_source_value_and_finalize(actor, D_800E1A01);
    return 0;
}
