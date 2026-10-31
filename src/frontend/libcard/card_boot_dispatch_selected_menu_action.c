#include "common.h"
#include "frontend/libcard/menu_callbacks.h"
#include "frontend/libcard.h"

typedef card_boot_menu_table CallbackTable;

// Copy the callback table locally and invoke the callback selected by the object.
void card_boot_dispatch_selected_menu_action(Object_800128C8 *object)
{
    CallbackTable callbacks;

    callbacks = D_800200A8;
    callbacks.cb[object->callback_index](object);
}
