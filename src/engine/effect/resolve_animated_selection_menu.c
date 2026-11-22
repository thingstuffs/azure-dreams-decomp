#include "common.h"
#include "engine/effect.h"
#include "engine/graphics.h"
#include "engine/menu.h"
#include "engine/node.h"
#include "shared/object_node.h"

typedef struct S_80050EF8_sub {
    u8 pad00[0x20];  /* +0x00: unknown, used by other functions */
    void *field20;   /* +0x20: arg passed to create_animated_selection_menu */
    void *pending_callback; /* +0x24 */
    void *field28;   /* +0x28: result object pointer */
} S_80050EF8_sub;

/* Lazily initializes and returns the result object, applying any pending value and registering a callback when ready. */
void *ensure_selection_menu_and_register_draw(ObjectNodeHeader *object)
{
    S_80050EF8_sub *object_state = NODE_BODY(object);

    if (object_state->field28 != 0 || (object_state->field28 = create_animated_selection_menu(object_state->field20)) != 0) {
        if (object_state->pending_callback != 0) {
            object->update_callback = object_state->pending_callback;
            object_state->pending_callback = 0;
        }
        register_node(object, (void *)draw_tinted_node_sprites_scratch);
    }
    return object_state->field28;
}
