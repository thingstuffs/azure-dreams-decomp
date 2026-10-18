#include "modules/dungeon_ovl_18ca83c.h"

void func_8002403C(void *target, s32 amount_input, void *owner) {
    s32 base_amount;
    register s32 adjusted_amount;

    if (try_trigger_target_record_effect(target, 2) == 0) {
        base_amount = get_random_scaled_value(amount_input & 0xFF) + 16;
        adjusted_amount = base_amount;
        if (*(u8 *)((u8 *)target + 0x28) & 2) {
            adjusted_amount = base_amount + ((s32)(base_amount << 16) >> 19);
        }
        *(u16 *)((u8 *)target + 0x64) += adjusted_amount;
        cap_pending_actor_value_delta(target);
        base_amount = 0x8004;
        create_actor_value_popup(base_amount, target, (s16)*(u16 *)((u8 *)target + 0x64), 1);
        apply_clamped_actor_value_delta(target);
    }
}

