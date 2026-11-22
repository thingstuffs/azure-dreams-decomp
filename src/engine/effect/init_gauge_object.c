#include "common.h"
#include "engine/effect.h"
#include "engine/menu/selection_menu.h"

extern void set_gauge_context(void *a0, void *a1);
extern void initialize_gauge_menu_display_rows(void *a0, void *a1, void *a2);

/* Reinitializes the object, sets up its sub-objects, and initializes its linked object. */
void init_gauge_object(MenuSelectionBody *object, void *context)
{
    set_gauge_context(object, context);
    init_gauge_blocks(object, &object->gauge, &object->gauge_block, &object->gauge_vector);
    initialize_gauge_menu_display_rows(object->widgets, object, context);
}
