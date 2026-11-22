#include "slus/saved_value_b98.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "engine/item.h"
#include "slus.h"

#include "engine/menu/selection_menu.h"

/* Releases the attachment and effect parts, restores the saved value, and sets completion flags. */
void destroy_selection_menu_and_release_owner(ObjectNodeHeader *object)
{
    MenuSelectionBody *state = NODE_BODY(object);
    s32 global_flags;
    u16 object_flags;

    destroy_animated_selection_menu(state->attachment);
    state->attachment = 0;
    selection_menu_saved_value = state->selected_entry;
    release_null_terminated_entries(state->buffers);
    state->owner->flags |= 0x8000;
    global_flags = object_flag_block.flags;
    object_flags = object->flags;
    *(s32 *)0x800814A0 = global_flags | 0x8000;
    object->flags = object_flags | 0x8000;
}
