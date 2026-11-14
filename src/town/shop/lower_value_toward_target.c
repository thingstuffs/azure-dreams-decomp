#include "common.h"
#include "shared/object_node.h"
#include "town/shop.h"

typedef void (*Callback)(void *, s32);

extern void refresh_money_display(void *);

typedef struct S_800B1890_0 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800B1890_0;

typedef struct ValueTransition {
    s32 unused;
    u16 target;
    u16 pad_06;
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
    current_value = state->unk_08;
    current_bits = ((u16)state->unk_08);
    if (target_value < current_value) {
        adjustment = current_value + 4;
        adjustment = target_value - adjustment;
        adjustment >>= 2;
        state->unk_08 = current_bits + adjustment;
    } else {
        state->unk_08 = ((ValueTransition *)object)->target;
        (object)[-1].update_callback = refresh_money_display;
    }

    refresh_money_display(object);
}
