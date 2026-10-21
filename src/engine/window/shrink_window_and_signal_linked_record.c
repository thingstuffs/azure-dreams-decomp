#include "common.h"

#include "common.h"
#include "engine/effect.h"
#include "engine/window.h"

typedef struct Func800359FCState Func800359FCState;
typedef struct Func800359FCEvent Func800359FCEvent;

typedef void (*Func800359FCCallback)(Func800359FCState *, Func800359FCEvent *, void *);

struct Func800359FCState {
    void *clear_target;
    u8 pad04[0x40];
    u8 *cursor_base;
    u8 enabled;
    u8 pad49;
    s16 cursor_offset;
    u8 pad4c[0x1c];
    Func800359FCCallback callback;
};

struct Func800359FCEvent {
    u8 pad00[2];
    s16 value;
};

extern void shrink_window_and_signal_linked_record(Func800359FCState *, Func800359FCEvent *, void *);

/* Dispatches the event callback, switching handlers when the cursor marker is 0xFE. */
void dispatch_window_fade_and_update_extents(Func800359FCState *state, Func800359FCEvent *event, void *callback_data) {
    u8 *base;
    s16 offset;
    u8 *cursor;

    if (unlink_cursor_when_finished(state) == 0) {
        if (state->enabled != 0) {
            base = state->cursor_base;
            offset = state->cursor_offset;
            cursor = base + offset;
            if (cursor[0x4C] == 0xFE) {
                begin_fade_to_black();
                state->callback = shrink_window_and_signal_linked_record;
            }
        }
        state->callback(state, event, callback_data);
        update_window_extents(state, event->value);
    }
}
