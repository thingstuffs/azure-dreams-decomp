#include "common.h"
#include "frontend/libcard.h"
/* Update the base record and pass its paired fields to the next helper. */
void card_boot_return_from_save_menu(CardSaveMenuBody *menu) {
    release_card_record_handles(NODE_HEADER(menu));
    init_card_boot_request_object(menu->request, menu->mode);
}
