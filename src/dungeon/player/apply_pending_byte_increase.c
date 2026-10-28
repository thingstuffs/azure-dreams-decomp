#include "common.h"
#include "shared/entity.h"

/* Apply the pending increase, clamp to the limit, and clear the pending value. */
void apply_pending_byte_increase(void *unused_0, s32 unused_1, void *unused_2, ActorRecord *object) {
    u8 updated_value;
    u8 value_limit;
    u8 pending;

    updated_value = object->hp;
    pending = object->hp_delta;
    updated_value += pending;
    value_limit = object->max_hp;
    object->hp = updated_value;
    if (value_limit < (u32) (updated_value & 0xFF)) {
        object->hp = value_limit;
    }
    object->hp_delta = 0;
}
