#include "common.h"
#include "shared/object_node.h"
#include "town/shop.h"

typedef void (*Callback)(void *, s32);

extern void refresh_formatted_global_display(void *);

typedef struct S_800B1890_0 {
    u8 pad_00[0x8];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
} S_800B1890_0;

typedef struct ValueTransition {
    s32 unused;
    union { s32 word; u16 low_half; } target;
    u8 pad_08[0x34];
    void *state;
} ValueTransition;

/* Lowers the state's value toward the target, or snaps to it and switches callbacks. */
void lower_value_toward_target(ObjectNodeHeader *object) {
    S_800B1890_0 *state;
    s32 target_value;
    s32 current_value;
    u16 current_bits;
    s32 adjustment;

    state = ((ValueTransition *)object)->state;
    target_value = *(s32 *)&object->pprev;
    current_value = state->unk_08.s;
    current_bits = state->unk_08.u;
    if (target_value < current_value) {
        adjustment = current_value + 4;
        adjustment = target_value - adjustment;
        adjustment >>= 2;
        state->unk_08.s = current_bits + adjustment;
    } else {
        state->unk_08.u = ((ValueTransition *)object)->target.low_half;
        (object)[-1].update_callback = refresh_formatted_global_display;
    }

    refresh_formatted_global_display(object);
}
