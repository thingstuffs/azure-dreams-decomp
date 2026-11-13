#include "shared/object_node.h"
#include "frontend/libcard/card_chooser.h"
#include "common.h"



#include "modules/main_server_ship_interfaces.h"
#include "frontend/libcard/interfaces.h"
#include "engine/menu.h"
#include "frontend/libcard.h"

/* Initializes record values and installs its callback pointer. */
void card_boot_create_menu_child_panels(CardChooserBody *chooser) {
    void *record = chooser;
    s32 record_base;

    record_base = record - 0x20;
    chooser->backdrop = create_or_reset_seven_entry_menu_backdrop(record_base, record + 0xC);
    chooser->choices = card_boot_create_or_reset_paired_choice_panel(record_base, chooser->selected_channel);
    card_boot_toggle_channel();
    ((ObjectNodeHeader *)record - 1)->update_callback = &card_boot_update_card_chooser_input;
}
