#include "common.h"
#include "frontend/libcard/card_chooser.h"
#include "frontend/card.h"
#include "town/devkit.h"
#include "frontend/card/server_imports.h"
#include "frontend/card/server_aliases.h"

extern u8 D_8040086C[];
extern u8 D_80400894[];
extern s32 D_8008DAB0[4];

/* Processes the object's two handles and sets the object and global high-bit flags. */
void mark_card_dev_object_handles_dirty(ObjectNodeHeader *node) {
    CardChooserBody *menu;
    u16 object_flags;
    s32 global_flags;

    if (node == 0) {
        printf_8007C040(D_8040086C, D_80400894, 0x183);
        exit_8007BEF0(1);
    }

    menu = NODE_BODY(node);
    card_dev_flag_object_dirty(menu->backdrop);
    assert_card_slot_and_set_high_bit(menu->choices);

    object_flags = node->flags;
    global_flags = card_ui_dirty_flags;
    object_flags |= 0x8000;
    global_flags |= 0x8000;
    node->flags = object_flags;
    D_8008DAB0[1] = global_flags;
}
