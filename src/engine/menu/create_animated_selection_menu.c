#include "shared/object_node.h"
#include "common.h"
#include "engine/menu.h"
#include "engine/runtime.h"
#include "slus.h"

/* Allocates and initializes an object, installs its callbacks, or returns NULL on failure. */
void *create_animated_selection_menu(void *init_data)
{
    ObjectNodeHeader *obj;
    AnimatedSelectionMenuBody *sub;

    obj = allocate_flagged_object_node(0);
    if (obj != 0) {
        sub = NODE_BODY(obj);
        initialize_menu_record_value(sub);
        sub->selected_index = find_resolved_selection_menu_index(sub, init_data);
        if (create_animated_selection_menu_entries(sub) == 0) {
            destroy_animated_selection_menu(obj);
            obj = 0;
        } else {
            obj->update_callback = update_animated_selection_menu;
            sub->animate = animate_selection_menu_entry_spacing;
        }
    }
    return obj;
}
