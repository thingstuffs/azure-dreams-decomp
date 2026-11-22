#include "shared/object_node.h"
#include "common.h"
#include "frontend/libcard/message.h"
#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"

/* Placed copy of card_boot_enter_copying_progress. */
extern void func_800263C0(CardSaveMenuBody *menu);


/* Selects card_boot_update_save_slot_menu_input when the state field is nonzero or enters copying progress. */
void card_boot_handle_overwrite_answer(CardSaveMenuBody *menu) {
    if (menu->overwrite_answer != 0) {
        NODE_HEADER(menu)->update_callback = card_boot_update_save_slot_menu_input;
        return;
    }
    func_800263C0(menu);
}
