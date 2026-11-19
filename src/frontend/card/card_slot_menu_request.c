/* Card slot menu request and its file-private helper. */
#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/libcard/slot_menu.h"
static void card_boot_set_slot_menu_request(CardSlotMenuState *object, struct ObjectNodeHeader *request) {
    object->request = request;
}

/* Calls card_boot_set_slot_menu_request with object, value. */
void card_boot_initialize_slot_menu_request(struct CardSlotMenuState *object, struct ObjectNodeHeader *request) {
    card_boot_set_slot_menu_request(object, request);
}
