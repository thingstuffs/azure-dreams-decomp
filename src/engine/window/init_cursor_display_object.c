#include "common.h"

#include "common.h"
#include "engine/window.h"
#include "engine/graphics.h"
#include "shared/entity.h"
#include "shared/object_node.h"

struct WindowCursorBody;
struct SpriteFrameState;

/* Initialize the display object and update its initial appearance. */
void init_cursor_display_object(void *object_arg, void *display, s32 *data, s16 data_index,
                   s16 table_offset, void *list_head) {
    ObjectNodeHeader *object = object_arg;

    create_blinking_cursor_object(object, display, data, data_index, table_offset, list_head);
    update_blinking_cursor_with_bright_idle(NODE_BODY(object),
                  object->position,
                  object->sprite);
}
