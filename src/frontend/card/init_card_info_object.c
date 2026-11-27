#include "frontend/card/slot_details.h"
#include "common.h"
#include "shared/object_node.h"
#include "frontend/card.h"
#include "main/data.h"
#include "town/menu.h"
#include "frontend/card/server_imports.h"
#include "frontend/libcard.h"
#include "frontend/card/server_aliases.h"

typedef struct {
    u8 pad_00[0xC];
    MenuDisplayNode *template_node;
    void *update_callback;
    u8 pad_14[0xA];
    u16 flags;
} Root;

extern Root D_8040B4F8;

/* Initializes the memory card information object and its working state. */
void *init_card_info_object(ObjectNodeHeader *owner, s32 info_value) {
    Root *base;
    CardDevSlotDetails *card_state;

    base = &D_8040B4F8;
    card_state = NODE_BODY(base);
    if (func_80047FD8(base) == 0) {
        base = func_8003C714(0, base, 0x387);
        if (base == 0) {
            printf_8007C040(card_info_assert_format, card_info_assert_filename, 0x1A0);
            exit_8007BEF0(1);
        }
        func_80040560(base, card_dev_render_panel_hierarchy);
    } else {
        card_dev_refresh_info_object(base);
        D_8040B4F8.flags &= 0x7FFF;
        bzero_8007BFE0(card_state, 0xDFC);
    }
    card_state->selected_slot = info_value;
    initialize_menu_primitive_entries(card_state, 0x15);
    base->template_node = &card_state->template_node;
    card_state->template_node.next = register_owner_handler_table(card_state->entries);
    initialize_menu_overlay_objects(card_state, owner);
    base->update_callback = 0;
    return base;
}
