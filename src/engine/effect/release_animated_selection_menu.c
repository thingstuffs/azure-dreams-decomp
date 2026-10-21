#include "common.h"
#include "engine/node.h"
#include "engine/runtime.h"

typedef struct {
    u8 pad0[0x24];
    s32 unk24;
    s32 unk28;
} S_80050EA8_sub;

typedef struct {
    u8 pad0[0x10];
    s32 unk10;
    u8 pad14[0x0C];
    S_80050EA8_sub unk20;
} S_80050EA8;

/* Saves the pending value, unlinks the object, and releases and clears its attachment. */
void release_selection_menu_and_preserve_pending_value(S_80050EA8 *object)
{
    s32 pending_value = object->unk10;
    S_80050EA8_sub *object_state = &object->unk20;

    if (pending_value != 0) {
        object_state->unk24 = pending_value;
        object->unk10 = 0;
    }
    unlink_node(object);
    destroy_animated_selection_menu((void *)object_state->unk28);
    object_state->unk28 = 0;
}
