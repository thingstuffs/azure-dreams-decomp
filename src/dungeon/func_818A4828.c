#include "modules/dungeon_ovl_18c4828.h"

void func_80024028(void *target, s32 effect_param) {
    s32 base_gain;
    register s32 stat_gain;

    if (try_trigger_target_record_effect(target, 1) == 0) {
        base_gain = get_random_scaled_value(effect_param & 0xFF) + 4;
        stat_gain = base_gain;
        if (*(u8 *)((u8 *)target + 0x28) & 1) {
            stat_gain = base_gain + ((s32)(base_gain << 16) >> 17);
        }
        *(u16 *)((u8 *)target + 0x64) += stat_gain;
        cap_pending_actor_value_delta(target);
        base_gain = 0x8004;
        create_actor_value_popup(base_gain, target, (s16)*(u16 *)((u8 *)target + 0x64), 1);
        apply_clamped_actor_value_delta(target);
    }
}

