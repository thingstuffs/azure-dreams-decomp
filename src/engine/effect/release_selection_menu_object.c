#include "common.h"
#include "engine/node.h"
#include "engine/runtime.h"

#include "shared/object_node.h"
#include "engine/menu/selection_menu.h"

/* Saves the pending value, unlinks the object, and releases and clears its attachment. */
void release_selection_menu_object(ObjectNodeHeader *object)
{
    void *pending_callback = object->update_callback;
    MenuSelectionBody *state = NODE_BODY(object);

    if (pending_callback != 0) {
        state->pending_callback = pending_callback;
        object->update_callback = 0;
    }
    unlink_node(object);
    destroy_animated_selection_menu(state->attachment);
    state->attachment = 0;
}
