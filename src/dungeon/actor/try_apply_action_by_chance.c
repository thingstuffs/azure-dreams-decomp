#include "common.h"

extern s32 roll_chance_and_run_action(void *, s16, s16);
extern void adjust_source_value_and_finalize(void *, const u8 *);
extern void wrap_position_and_set_state_value(s32);
extern u8 D_800E1A1D[];
extern u8 D_800E1A2D[];
extern s32 D_800DCF0C;

/* Apply the second chance-based status and select its result message. */
s32 try_apply_action_by_chance(void *actor, s32 chance, s32 action)
{
    if (roll_chance_and_run_action(actor, (s16)chance, (s16)action)) {
        adjust_source_value_and_finalize(actor, D_800E1A1D);
        if (((u8 *)actor)[0x13] == 0) {
            wrap_position_and_set_state_value(D_800DCF0C);
        }
        return 1;
    }
    adjust_source_value_and_finalize(actor, D_800E1A2D);
    return 0;
}
