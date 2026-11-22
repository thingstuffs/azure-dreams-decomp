#include "frontend/libcard/state.h"
#include "shared/object_node.h"

void card_boot_enter_damaged_card_notice(CardChooserBody *chooser)
{
    chooser->resume_input = card_boot_update_card_chooser_input;
    card_boot_show_damaged_memory_card_notice(NODE_HEADER(chooser));
    NODE_HEADER(chooser)->update_callback = card_boot_poll_status_and_dismiss_dialog;
}
