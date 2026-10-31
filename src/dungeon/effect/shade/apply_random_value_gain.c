#include "common.h"
#include "dungeon/effect/shade.h"
#include "dungeon/effect.h"

typedef struct Obj {
    u8 pad00[0x28];
    u8 flags;
    u8 pad29[0x3B];
    u16 value64;
} Obj;

#include "dungeon/effect/screen.h"
#include "dungeon/actor.h"
extern s32 get_random_scaled_value(s16 input_value);

/* Applies a flag-adjusted value increase and updates the target. */
void apply_random_value_gain(ActorRecord *target, s32 amount_param, ActorRecord *record)
{
    s32 base_amount;
    register s32 adjusted_amount;

    if (try_trigger_target_record_effect(target, 4, record) == 0) {
        base_amount = get_random_scaled_value(amount_param & 0xFF) + 0x10;
        adjusted_amount = base_amount;
        if (target->hp & 1) {
            adjusted_amount = base_amount + ((s16)base_amount >> 1);
        }
        target->hp_delta += adjusted_amount;
        cap_pending_actor_value_delta(target);
        base_amount = 0x8004;
        create_actor_value_popup(base_amount, target, (s16)target->hp_delta, 1);
        apply_clamped_actor_value_delta(target);
    }
}
