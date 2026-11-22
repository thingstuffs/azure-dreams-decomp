#include "common.h"
#include "shared/object_node.h"
#include "engine/menu.h"

extern void release_selection_menu_object(ObjectNodeHeader *object);

/* Checks sub-state, restores the saved callback and cleans up on a nonzero result, then returns the result. */
s32 run_state_callback_and_restore(MenuSelectionBody *state)
{
    s32 check_result = call_menu_state_callback(state);

    if (check_result != 0) {
        NODE_HEADER(state)->update_callback = state->saved_callback;
        release_selection_menu_object(NODE_HEADER(state));
    }
    return check_result;
}
