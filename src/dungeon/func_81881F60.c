#include "modules/dungeon_ovl_18a0800.h"
#include "common.h"

extern s32 try_trigger_target_record_effect(s32, s32);
extern s32 set_or_clear_actor_status_slot(s32, s32, s32);
extern void adjust_source_value_and_finalize(s32, void *);
extern u8 D_800E1CD5[9];

/* Conditionally applies D_800E1CD5 using a check indexed by the supplied value's low byte. */
void apply_indexed_effect_condition(s32 target, u8 packedValue, void *owner_context) {
    if (try_trigger_target_record_effect(target, 1) == 0) {
        s32 valueGroupIndex = packedValue >> 2;
        valueGroupIndex += 2;
        if ((set_or_clear_actor_status_slot(target, 0x15, valueGroupIndex) << 16) != 0) {
            adjust_source_value_and_finalize(target, D_800E1CD5);
        }
    }
}
