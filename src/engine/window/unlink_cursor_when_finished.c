#include "common.h"
#include "shared/object_node.h"

#include "engine/node.h"
#include "engine/object.h"
#include "engine/object/runtime_linked_node.h"
#include "engine/window.h"

/* The cursor and attached-message bodies put the script, enabled flag, entry
 * index and owner-list link at the same offsets after their render prefix. */
typedef struct WindowCleanupState {
    WindowRenderPrefix render;
    u8 pad_0C[0x38];
    u8 *cursor_base;
    u8 enabled;
    u8 pad49;
    s16 cursor_offset;
    u8 pad_4C[8];
    RuntimeLinkedNode owner_link;
} WindowCleanupState;

/* Cleans up and unlinks the node when its enabled cursor has status 0xFF. */
s32 unlink_cursor_when_finished(WindowRenderPrefix *render) {
    WindowCleanupState *state = (WindowCleanupState *)render;
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
    clear_word(&render->model->unk_00);
    unlink_owner_list_node(&state->owner_link);
    node = NODE_HEADER(render);
    unlink_node(node);
    unlink_active_node(node);
    return 1;
}
