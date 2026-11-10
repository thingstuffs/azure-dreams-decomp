/* Set and initialize the memory card save menu request. */

#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"



/* Stores the supplied value in the object's field at offset 0x20. */

void card_boot_set_save_menu_request(CardSaveMenuBody *object, void *value) {
    object->request = value;
}

/* Set the object's field at offset 0x20 to the supplied value. */
void card_boot_initialize_save_menu_request(CardSaveMenuBody *object, void *value) {
    card_boot_set_save_menu_request(object, value);
}
