#include "shared/object_node.h"
#include "frontend/libcard/card_chooser.h"
#include "common.h"



#include "modules/main_server_ship_interfaces.h"
#include "frontend/libcard/interfaces.h"
#include "engine/menu.h"
#include "frontend/libcard.h"

/* Initializes record values and installs its callback pointer. */
void card_boot_create_menu_child_panels(CardChooserBody *chooser) {
    ObjectNodeHeader *owner;

    owner = NODE_HEADER(chooser);
    chooser->backdrop = create_menu_backdrop(owner, &chooser->selected_channel);
    chooser->choices = card_boot_create_choice_panel(owner, chooser->selected_channel);
    card_boot_toggle_channel();
    NODE_HEADER(chooser)->update_callback = &card_boot_update_card_chooser_input;
}
