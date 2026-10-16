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

extern void runtimeClearValue(s32 *value);
extern void runtimeUnlinkDoublyLinkedNode(void *node);
extern void func_80044A50(void *node);
extern void unlinkActiveNode(void *node);

/* Cleans up and unlinks the node when its enabled cursor has status 0xFF. */
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
    runtimeClearValue((s32 *)state->clear_target);
    runtimeUnlinkDoublyLinkedNode((u8 *)state + 0x54);
    state = (Func37534State *)((u8 *)state - 0x20);
    func_80044A50(state);
    unlinkActiveNode(state);
    return 1;
}
