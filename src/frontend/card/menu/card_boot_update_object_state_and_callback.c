#include "shared/pad_state.h"
#include "shared/object_node.h"
#include "common.h"
#include "frontend/card/menu.h"
#include "frontend/card/service.h"
#include "main/data.h"
#include "frontend/card.h"
#include "frontend/card/server_aliases.h"
#include "frontend/card/server_imports.h"

extern void forward_target_value_initcardmessageobject(void *left, void *right);

/* Updates the object's state and callback and performs a one-time transition. */
void card_boot_update_object_state_and_callback(CardChooserBody *object)
{
    s32 state_index;
    s32 table_offset;
    void (*next_callback)(CardChooserBody *);

    if ((boot_pad_state.held != 0) && ((boot_pad_state.pressed & 0x40) != 0)) {
        toggle_card_selection_state();
        object->wait_notice_state = 0;
        NODE_HEADER(object)->update_callback = card_boot_handle_menu_selection_input;
        return;
    }

    state_index = card_devkit_poll_stable_slot_state();
    table_offset = state_index * 4;
    card_diagnostic_printf_8003FA78(dev_card_index_and_status_format, object->selected_channel, dev_card_slot_status_names[state_index]);
    card_dev_print_status();
    if (state_index != 0) {
        object->wait_notice_state = 0;
        object->slot_status = state_index;
        next_callback = D_804090E0[state_index];
        object->unk_34 = state_index;
        NODE_HEADER(object)->update_callback = next_callback;
        return;
    }
    if ((card_dev_get_op_state() == 3) && (object->wait_notice_state == 0)) {
        forward_target_value_initcardmessageobject(NODE_HEADER(object), &object->wait_notice_state);
        object->wait_notice_state = 1;
    }
    (void)table_offset;
}
