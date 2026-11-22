#include "slus/saved_value_b98.h"
#include "shared/object_node.h"
#include "slus.h"
#include "engine/effect.h"
#include "engine/menu/selection_menu.h"

extern s32 D_800814A0_abs __attribute__((section(".data")));
/* Starts the fade callback, releases the attachment, and sets global and child flags. */
void begin_selection_menu_teardown_and_fade(ObjectNodeHeader *object)
{
    MenuSelectionBody *state = NODE_BODY(object);
    s32 saved_value;
    ObjectNodeHeader *attachment;
    ObjectNodeHeader *child;
    if (object != 0) {
        state->fade_ticks = 2;
        saved_value = state->selected_entry;
        attachment = state->attachment;
        NODE_HEADER(state)->update_callback = fade_effect_parts;
        selection_menu_saved_value = saved_value;
        destroy_animated_selection_menu(attachment);
        child = state->owner;
        D_800814A0_abs |= 0x8000;
        child->flags |= 0x8000;
        state->attachment = 0;
    }
}
