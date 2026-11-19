#include "common.h"
#include "engine/menu.h"

/* Call the object's callback, then run its follow-up routine. */
void update_animated_selection_menu(AnimatedSelectionMenuBody *object) {
    object->animate(object);
    handle_animated_selection_menu_input(object);
}
