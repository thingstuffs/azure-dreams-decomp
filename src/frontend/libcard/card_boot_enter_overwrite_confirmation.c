#include "common.h"
#include "frontend/libcard/save_menu.h"
#include "m2c_compat.h"

#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"
#include "main/data.h"

/* Set record pointers around an update of its embedded data. */
void card_boot_enter_overwrite_confirmation(CardSaveMenuBody *menu) {
    menu->saved_callback = &card_boot_handle_overwrite_answer;
    card_boot_show_overwrite_confirmation(NODE_HEADER(menu), &menu->overwrite_answer);
    NODE_HEADER(menu)->update_callback = &D_800261F0;
}
