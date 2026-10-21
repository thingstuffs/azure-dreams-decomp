#include "common.h"

#include "common.h"
#include "engine/node.h"
#include "engine/object.h"
#include "engine/window.h"

typedef struct RuntimeObject {
    void *sub;
    u8 pad04[0x40];
    u8 *base;
    u8 active;
    u8 pad49;
    s16 index;
    u8 state;
    u8 state2;
    u8 pad4E[0x1A];
    void (*handler)(struct RuntimeObject *, s32, s32, s32);
} RuntimeObject;

/* Handles active-object state transitions and dispatches the object's handler. */
void update_window_state(RuntimeObject *object, s32 handler_arg1, s32 handler_arg2, s32 state)
{
    u8 *entry;
    s32 unset = 0xFF;

    if (object->active != 0) {
        entry = object->base;
        entry += object->index;
        state = entry[0x4C];

        if (state == unset) {
            entry[0x50] = 1;
            runtime_clear_value(object->sub);
            runtime_unlink_doubly_linked_node((u8 *)object + 0x54);
            object = (RuntimeObject *)((u8 *)object - 0x20);
            unlink_node(object);
            unlink_active_node(object);
            return;
        }

        if (state == 0xFE) {
            object->state = unset;
            object->state2 = unset;
            object->handler = advance_cursor_extent;
        }
    }

    object->handler(object, handler_arg1, handler_arg2, state);
}
