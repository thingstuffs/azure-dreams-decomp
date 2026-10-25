#include "common.h"

extern void adjust_source_value_and_finalize(void *context, const void *source);
extern s32 roll_threshold_effect_variant_b(void *entity, s16 chance, s16 effect_value);
extern s32 wrap_position_and_set_state_value(s32 state_value);
extern s32 D_800DCF14;
extern u8 D_800E191B[];
extern u8 D_800E1A44[];

/* Attempt to apply a status effect and display the result. */
s32 try_apply_threshold_effect_variant_b(void *entity, s16 chance, s16 effect_value) {
    if (roll_threshold_effect_variant_b(entity, chance, effect_value) != 0) {
        adjust_source_value_and_finalize(entity, D_800E1A44);
        if (*(u8 *)((u8 *)entity + 0x13) == 0) {
            wrap_position_and_set_state_value(D_800DCF14);
        }
        return 1;
    }
    if ((*(s32 *)((u8 *)entity + 0x1C) & 0x10) == 0) {
        adjust_source_value_and_finalize(entity, D_800E191B);
    }
    return 0;
}
