#include "frontend/card.h"
#include "frontend/card/menu.h"
#include "main/data.h"

/* Card status 4 in the server: show the no-memory-card notice. */
void card_dev_open_no_memory_card_dialog(CardChooserBody *menu) {
    menu->resume_input = card_boot_handle_menu_selection_input;
    card_dev_show_no_memory_card_notice(NODE_HEADER(menu));
    NODE_HEADER(menu)->update_callback = D_80407D90;
}
