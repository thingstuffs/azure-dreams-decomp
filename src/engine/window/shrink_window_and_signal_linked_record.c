#include "common.h"

#include "engine/effect.h"
#include "engine/window.h"

#include "engine/window/attached_message_window.h"

typedef void (*AttachedWindowHandler)(AttachedMessageWindowBody *, ObjectPosition *, SpriteFrameState *);

/* Each attached-window update forwards the node position and sprite to its current handler. */
void dispatch_window_fade_and_update_extents(AttachedMessageWindowBody *state, ObjectPosition *position, SpriteFrameState *sprite) {
    AttachedWindowHandler handler;
    u8 *base;
    s16 offset;
    u8 *cursor;

    if (unlink_cursor_when_finished(&state->render) == 0) {
        if (state->active != 0) {
            base = state->parent_window;
            offset = state->object_id;
            cursor = base + offset;
            if (cursor[0x4C] == 0xFE) {
                begin_fade_to_black();
                state->handler = shrink_window_and_signal_linked_record;
            }
        }
        handler = state->handler;
        handler(state, position, sprite);
        update_window_extents(state, position->x.w.i);
    }
}
