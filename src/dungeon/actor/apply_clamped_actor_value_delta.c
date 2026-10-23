#include "shared/actor_status_ids.h"
#include "common.h"

typedef struct {
    u8 pad28[0x28];
    u8 value;
    u8 limit;
    u8 pad2a[0x3A];
    s16 delta;
} FuncState;

extern s32 get_entity_effect_value(void *entry, s32 effect_id);

/* Apply and clear the value delta, clamping the result to the byte range and state limit. */
void apply_clamped_actor_value_delta(void *entity) {
    FuncState *state = (FuncState *)entity;
    s32 value;

    if ((state->delta < 0) && ((get_entity_effect_value(entity, STATUS_DAMAGE_GUARD) << 16) != 0)) {
        state->delta = 0;
    }

    value = state->value;
    value += state->delta;
    if (value < 0) {
        value = 0;
    } else if (value >= 0x100) {
        value = 0xFF;
    }
    state->value = (u8)value;
    value = state->limit;
    state->delta = 0;
    if ((u32)value < state->value) {
        state->value = (u8)value;
    }
}
