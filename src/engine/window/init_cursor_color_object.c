#include "engine/window/cursor_source.h"
#include "common.h"

#include "engine/window.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "slus/window_choice_data.h"

/* Initialize the object, install its color update callback, and run it once. */
void init_cursor_color_object(MenuChoiceCursorStorage *object_arg, Rec_D_80081FDC *model, WindowCursorSource *data, s16 index, s16 table_index, void *list) {
    ObjectNodeHeader *node = &object_arg->node;
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
