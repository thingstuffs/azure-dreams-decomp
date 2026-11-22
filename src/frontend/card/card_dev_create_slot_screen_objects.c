#include "common.h"
#include "frontend/card/menu.h"
#include "frontend/card.h"

/*
 * Creates the card background and slot objects, saves their handles, runs the screen setup, and
 * installs card_boot_handle_menu_selection_input.
 */
void card_dev_create_slot_screen_objects(CardChooserBody *menu) {
    ObjectNodeHeader *owner = NODE_HEADER(menu);
    menu->backdrop = init_card_background_object(owner, &menu->selected_channel);
    menu->choices = init_card_slot_object(owner);
    toggle_card_selection_state();
    owner->update_callback = card_boot_handle_menu_selection_input;
}
