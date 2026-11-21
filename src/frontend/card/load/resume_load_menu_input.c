#include "common.h"
#include "frontend/card/load.h"
#include "main/data.h"
#include "frontend/card/server_aliases.h"

/*
 * Installs handle_menu_selection_input when the operation word at offset 0x38 is nonzero, or runs
 * card_dev_enter_saving_progress otherwise.
 */
void resume_load_menu_input(void *ptr) {
    if (*(s32 *)((u8 *)ptr + 0x38) != 0) {
        *(s32 *)((u8 *)ptr - 16) = (s32)handle_menu_selection_input;
        return;
    } else {
        card_dev_enter_saving_progress(ptr);
    }
}
