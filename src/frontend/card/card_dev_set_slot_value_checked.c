#include "shared/object_node.h"
#include "frontend/card/choice_panel.h"
#include "common.h"
#include "frontend/card/slot_assert_bytes.h"
#include "frontend/card.h"
#include "frontend/card/server_imports.h"





/* Assert a valid card slot, store its value, and process its embedded state. */
void card_dev_set_slot_value_checked(ObjectNodeHeader *node, s32 slot_value) {
    CardDevSlotMenu *panel;

    panel = NODE_BODY(node);
    if (node == 0) {
        printf_8007C040(card_slot_assert_format, card_slot_filename, 0x153);
        exit_8007BEF0(1);
    }
    panel->selection = slot_value;
    update_two_slots_using_selection_mapping(panel);
}
