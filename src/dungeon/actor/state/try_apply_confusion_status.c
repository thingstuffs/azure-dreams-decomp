#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/item/message.h"

extern s32 generate_random_value(void);
extern s32 set_or_clear_actor_status_slot(void *ptr, s32 value, s32 kind);
extern void wrap_position_and_set_state_value(s32 value);

extern s32 D_800DCF10[];
extern u8 D_800E1A55[];

/* Apply an entity effect when a random roll passes its threshold. */
s32 try_apply_confusion_status(void *ptr, s32 threshold_input, s32 kind_input) {
    s32 value;
    u16 threshold = threshold_input;
    s16 kind = kind_input;
    s32 roll;
    register s32 signed_threshold;
    s32 rng_result;

    rng_result = generate_random_value();
    value = *(u8 *)((u8 *)ptr + 3);
    signed_threshold = rng_result & 0xFFFF;
    if (value != 0) {
        s32 divisor = (*(u32 *)ptr) >> 24;
        roll = signed_threshold % divisor;
    } else {
        roll = 0;
    }

    signed_threshold = ((s32)((u32)threshold << 16)) >> 16;
    if ((((s32)(roll < signed_threshold)) != 0) || (signed_threshold == 0xFF)) {
        if ((s16)set_or_clear_actor_status_slot(ptr, STATUS_CONFUSION, (s8)kind) >= 0) {
            adjust_source_value_and_finalize(ptr, D_800E1A55);
            if (*(u8 *)((u8 *)ptr + 0x13) == 0) {
                wrap_position_and_set_state_value(D_800DCF10[0]);
            }
            return 1;
        }
    }

    return 0;
}
