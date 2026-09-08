#include "common.h"

#include "common.h"

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

extern s32 func_80037534(Func800359FCState *arg0);
extern void func_8003C24C(void);
extern void func_80035CE4(Func800359FCState *arg0, Func800359FCEvent *arg1, void *arg2);
extern void func_80037C7C(Func800359FCState *arg0, s16 arg1);

/* Dispatches the event callback, switching handlers when the cursor marker is 0xFE. */
void func_800359FC(Func800359FCState *state, Func800359FCEvent *event, void *callback_data) {
    u8 *base;
    s16 offset;
    u8 *cursor;

    if (func_80037534(state) == 0) {
        if (state->enabled != 0) {
            base = state->cursor_base;
            offset = state->cursor_offset;
            cursor = base + offset;
            if (cursor[0x4C] == 0xFE) {
                func_8003C24C();
                state->callback = func_80035CE4;
            }
        }
        state->callback(state, event, callback_data);
        func_80037C7C(state, event->value);
    }
}
