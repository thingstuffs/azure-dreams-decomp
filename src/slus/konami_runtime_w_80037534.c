#include "common.h"

#include "common.h"

typedef struct Func37534State {
    u8 *clear_target;
    u8 pad04[0x40];
    u8 *cursor_base;
    u8 enabled;
    u8 pad49;
    s16 cursor_offset;
} Func37534State;

extern void func_80033C84(s32 *arg0);
extern void func_80035090(void *arg0);
extern void func_80044A50(void *arg0);
extern void func_8003FFF0(void *arg0);

/* Mark an enabled cursor with status 0xFF and run its cleanup callbacks. */
s32 func_80037534(Func37534State *state) {
    u8 *cursor_base;
    s16 cursor_offset;
    u8 *cursor;

    if (state->enabled == 0) {
        return 0;
    }

    cursor_base = state->cursor_base;
    cursor_offset = state->cursor_offset;
    cursor = cursor_base + cursor_offset;
    if (cursor[0x4C] != 0xFF) {
        return 0;
    }

    cursor[0x50] = 1;
    func_80033C84((s32 *)state->clear_target);
    func_80035090((u8 *)state + 0x54);
    state = (Func37534State *)((u8 *)state - 0x20);
    func_80044A50(state);
    func_8003FFF0(state);
    return 1;
}
