#include "common.h"

#include "common.h"
#include "engine/window.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"

extern void update_blinking_cursor_with_dark_idle(void *, ObjectPosition *, void *);

/* Initialize the object, install its color update callback, and run it once. */
void init_cursor_color_object(void *object_arg, void *model, s32 *data, s16 index, s16 table_index, void *list) {
    ObjectNodeHeader *node = object_arg;
    WindowCursorBody *state;
    ObjectPosition *position;
    SpriteFrameState *sprite;

    create_blinking_cursor_object(node, model, data, index, table_index, list);
    state = NODE_BODY(node);
    position = node->position;
    sprite = node->sprite;
    node->update_callback = update_blinking_cursor_with_dark_idle;
    sprite->color.word = 0;
    update_blinking_cursor_with_dark_idle(state, position, sprite);
}
