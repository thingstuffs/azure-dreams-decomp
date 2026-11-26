#include "frontend/card.h"
#include "frontend/card/menu.h"
#include "frontend/card/server_imports.h"
#include "main/data.h"

/* Card status 5 in the server: show the damaged-card notice, then poll for its dismissal. */
void card_dev_open_damaged_card_dialog(CardChooserBody *menu) {
    menu->resume_input = card_boot_handle_menu_selection_input;
    func_804032D4(NODE_HEADER(menu));
    NODE_HEADER(menu)->update_callback = D_80407DB8;
}
