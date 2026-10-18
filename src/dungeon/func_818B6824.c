#include "modules/dungeon_ovl_18d6800.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"



/* Adds a computed gain to the target's stored value, doubling it when flagged. */
void interpolate_view_parameters(EntityRec *target, s32 gain_param, s32 ignored_context) {
    s32 base_gain;
    register s32 gain;

    if (try_trigger_target_record_effect(target, 1) == 0) {
        base_gain = get_random_scaled_value(gain_param & 0xFF) + 8;
        gain = base_gain;
        if (target->unk_28 & 1) {
            gain = base_gain << 1;
        }
        target->unk_64 = (u16) (((u16)target->unk_64) + gain);
        cap_pending_actor_value_delta(target);
        base_gain = 0x8004;
        create_actor_value_popup(base_gain, target, (s16) ((u16)target->unk_64), 1);
        apply_clamped_actor_value_delta(target);
    }
}
