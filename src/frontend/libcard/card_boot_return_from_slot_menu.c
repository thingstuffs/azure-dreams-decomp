#include "common.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"

/* Processes the object header and passes its stored value to init_card_boot_request_object. */
void card_boot_return_from_slot_menu(CardSlotMenuState *object_data) {
    card_boot_destroy_slot_selection_menu(NODE_HEADER(object_data));
    init_card_boot_request_object(object_data->request, 0);
}
