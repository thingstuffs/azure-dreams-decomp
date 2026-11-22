#include "frontend/card/save_image.h"
#include "common.h"
#include "frontend/card/load.h"
#include "frontend/card.h"
#include "shared/object_node.h"
#include "frontend/card/server_aliases.h"

extern void forward_value_initcardmessageobject(void *value);
extern void func_804069FC(void);
extern s32 D_80010208;

/* Updates the state and selects its next callback based on the current entry check. */
void finish_load_slot_check(CardDevLoadSlotScreen *screen)
{
    CardDevSaveWork *save = (CardDevSaveWork *)0x80010000;
    ObjectNodeHeader *state_base;
    s32 check_result;

    init_save_header_buffer(save, screen->selection,
                  screen->mode);
    check_result = process_entry_with_table_value(screen->selection, save);
    state_base = NODE_HEADER(screen);
    if (check_result == 0) {
        screen->state_callback = handle_menu_selection_input;
        forward_value_initcardmessageobject(state_base);
        state_base->update_callback = func_804069FC;
    } else {
        card_info_set_value_and_refresh(screen->information, screen->selection);
        card_dev_refresh_slot_window_display(screen->windows[screen->selection]);
        if (D_80010208 != 0) {
            state_base->update_callback = set_global;
        } else {
            state_base->update_callback = handle_menu_selection_input;
        }
    }
    reset_card_selection_state();
    screen->operation_state = 0;
}
