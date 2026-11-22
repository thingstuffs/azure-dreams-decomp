#include "common.h"
#include "frontend/card/load.h"
#include "main/data.h"
#include "shared/object_node.h"

#include "frontend/card/server_aliases.h"

/*
 * Installs handle_menu_selection_input when the operation word at offset 0x38 is nonzero, or runs
 * card_dev_enter_saving_progress otherwise.
 */
void resume_load_menu_input(CardDevLoadSlotScreen *screen) {
    if (screen->dialog_answer != 0) {
        NODE_HEADER(screen)->update_callback = handle_menu_selection_input;
        return;
    } else {
        card_dev_enter_saving_progress(screen);
    }
}
