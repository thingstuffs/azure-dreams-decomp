#include "frontend/card/server_menu.h"
#include "common.h"
#include "shared/object_node.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"
#include "frontend/libcard.h"
#include "frontend/card/server_aliases.h"

/* The imported symbol declares the first 0x120 bytes of the static node.
 * The constructor clears 0x180 bytes starting at its body. */
struct CardDevSmeObject {
    ObjectNodeHeader node;
    u8 body_prefix[0x100];
};

/* Initializes the memory card state object and its working data. */
ObjectNodeHeader *init_card_sme_object(struct CardDevLoadNode *owner) {
    ObjectNodeHeader *obj = &card_sme_object.node;
    CardDevMenu4 *card_state = NODE_BODY(obj);
    s32 state_value;

    if (func_80047FD8(obj) == 0) {
        obj = func_8003C714(0, obj, 0x68);
        if (obj == 0) {
            printf_8007C040(card_sme_assert_format, card_sme_assert_filename, 0xEE);
            exit_8007BEF0(1);
        }
        func_80040560(obj, card_dev_render_panel_hierarchy);
    } else {
        card_dev_refresh_options_object(obj);
        {
            u16 flags = card_sme_object.node.flags;
            flags &= 0x7FFF;
            card_sme_object.node.flags = flags;
        }
        bzero_8007BFE0(card_state, 0x180);
    }
    card_dev_init_sme_menu_entries(card_state, 4);
    obj->sprite = (struct SpriteFrameState *)&card_state->frame;
    state_value = dispatch_context_through_four_entry_table(card_state->entries);
    card_state->frame.unk_0C = state_value;
    card_dev_prepare_save_heading_layout(card_state, owner);
    return obj;
}
