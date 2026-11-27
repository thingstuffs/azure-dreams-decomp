#include "common.h"

#include "engine/script/vm.h"

#include "engine/window/attached_message_window.h"

/* Decreases value by 0x20, clamps it to 2, and updates the callback and data flag at the lower limit. */
void shrink_window_and_signal_linked_record(AttachedMessageWindowBody *state, ObjectPosition *position, void *unused_data) {
    u16 value;

    value = position->x.w.i - 0x20;
    position->x.w.i = value;
    if (position->x.w.i < 2) {
        u8 *data;
        s16 offset;

        position->x.w.i = 2;
        state->handler = noop_after_window_shrink;
        data = state->parent_window;
        offset = state->object_id;
        *(data + offset + 0x50) = 1;
    }
}
