#include "modules/dungeon_ovl_18d0850.h"

void follow_brighten(EntityRec *entity, s32 value_id) {
    if (try_trigger_target_record_effect(entity, 4) == 0) {
        s32 base_gain;
        s16 bonus;
        s32 gain;

        base_gain = get_random_scaled_value(value_id & 0xFF) + 8;
        bonus = entity->unk_28 & 4;
        gain = base_gain;
        if (bonus) {
            bonus = (s32) (base_gain << 16) >> 18;
            gain = base_gain + bonus;
        }
        entity->unk_64 = (u16) (((u16)entity->unk_64) + gain);
        cap_pending_actor_value_delta(entity);
        base_gain = 0x8004;
        create_actor_value_popup(base_gain, entity, (s16) ((u16)entity->unk_64), 1);
        apply_clamped_actor_value_delta(entity);
    }
}
