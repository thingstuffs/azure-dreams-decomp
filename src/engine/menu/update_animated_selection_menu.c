#include "common.h"
#include "engine/menu.h"

typedef struct S_8004FC2C {
    void (*func)(void *self);
} S_8004FC2C;

/* Call the object's callback, then run its follow-up routine. */
void update_animated_selection_menu(S_8004FC2C *object) {
    object->func(object);
    handle_animated_selection_menu_input(object);
}
