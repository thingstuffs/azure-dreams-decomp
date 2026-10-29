#include "common.h"
#include "dungeon/item.h"
struct State;

extern s32 roll_threshold_effect_variant_a(struct State *state_ptr, s16 limit_input, s16 byte_input);
extern void wrap_position_and_set_state_value(s32 state_value);

extern s32 D_800DCF1C[];
extern u8 D_800E19C2[];
extern u8 D_800E19D3[];

/* Attempt to apply a status effect to the target and report success or failure. */
s32 try_apply_status_effect(void *target, s16 chance, s16 duration) {
    if (roll_threshold_effect_variant_a(target, chance, duration) != 0) {
        adjust_source_value_and_finalize(target, D_800E19C2);
        if (*(u8 *)((u8 *)target + 0x13) == 0) {
            wrap_position_and_set_state_value(D_800DCF1C[0]);
        }
        return 1;
    }

    adjust_source_value_and_finalize(target, D_800E19D3);
    return 0;
}
