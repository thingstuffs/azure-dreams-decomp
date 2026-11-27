#include "frontend/card.h"
#include "frontend/card/menu.h"
#include "frontend/card/server_imports.h"
#include "main/data.h"

/* Card status 3 in the server: ask whether to format the card, then poll for the answer. */
void card_dev_open_format_confirmation_dialog(CardChooserBody *menu) {
    menu->resume_input = card_boot_init_chooser_callback;
    card_dev_show_format_confirmation(NODE_HEADER(menu), &menu->format_answer);
    NODE_HEADER(menu)->update_callback = D_80407DB8;
}
