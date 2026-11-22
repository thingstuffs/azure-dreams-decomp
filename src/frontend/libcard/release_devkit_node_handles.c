#include "common.h"
#include "frontend/libcard/card_chooser.h"
#include "frontend/card/server_aliases.h"
#include "frontend/card/server_imports.h"
#include "frontend/card.h"

extern const char D_8040086C[], D_80400894[];
/* Release the devkit node's two allocations and flag its completion. */
void release_devkit_node_handles(ObjectNodeHeader *node) {
    CardChooserBody *menu;

    if (node == 0) {
        printf_8007C040(D_8040086C, D_80400894, 0x183);
        exit_8007BEF0(1);
    }
    menu = NODE_BODY(node);
    card_dev_flag_object_dirty(menu->backdrop);
    assert_card_slot_and_set_high_bit(menu->choices);
    node->flags |= 0x8000;
    card_ui_dirty_flags |= 0x8000;
}
