#include "common.h"

#include "engine/menu.h"
#include "slus.h"

/* Resets the object's transition state, switches callbacks, and advances its saved value. */
void begin_selection_menu_index_change(AnimatedSelectionMenuBody *object, int target)
{
    object->transition_tick = 0;
    if (object->animate == animate_selection_menu_entry_spacing) {
        object->spacing = 0x20;
        animate_selection_menu_entry_spacing(object);
    }
    object->previous_index = object->selected_index;
    object->animate = animate_selection_menu_index_transition;
    object->selected_index = advance_index_with_single_wrap(object->selected_index, target, object->count);
}
