#include "common.h"
#include "shared/object_node.h"

#include "engine/node.h"
#include "engine/object.h"
#include "engine/window.h"

typedef struct Func37534State {
    u8 *clear_target;
    u8 pad04[0x40];
    u8 *cursor_base;
    u8 enabled;
    u8 pad49;
    s16 cursor_offset;
} Func37534State;

/* Cleans up and unlinks the node when its enabled cursor has status 0xFF. */
s32 unlink_cursor_when_finished(Func37534State *state) {
    u8 *cursor_base;
    s16 cursor_offset;
    u8 *cursor;
    ObjectNodeHeader *node;

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
    clear_word((s32 *)state->clear_target);
    unlink_owner_list_node((u8 *)state + 0x54);
    node = NODE_HEADER(state);
    unlink_node(node);
    unlink_active_node(node);
    return 1;
}
