#include "common.h"
#include "shared/object_node.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"
#include "frontend/libcard.h"
#include "frontend/card/server_aliases.h"
#include "frontend/card/server_menu.h"

extern s32 dispatch_context_through_four_entry_table(void *context);

typedef struct {
    u8 unk_00[0x0C];
    CardDevMenuEntry *heading;
} Obj;

typedef struct CardDevSmeObject {
    u8 unk_00[0x1E];
    u16 flags;
    u8 unk_20[0x100];
} Root;

/* Initializes the memory card state object and its working data. */
void * init_card_sme_object(struct ObjectNodeHeader *owner) {
    Obj *obj = (Obj *)&card_sme_object;
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
            u16 flags = card_sme_object.flags;
            flags &= 0x7FFF;
            card_sme_object.flags = flags;
        }
        bzero_8007BFE0(card_state, 0x180);
    }
    card_dev_init_sme_menu_entries(card_state, 4);
    obj->heading = &card_state->heading;
    state_value = dispatch_context_through_four_entry_table(card_state->entries);
    card_state->heading.unk_0C = state_value;
    card_dev_prepare_save_heading_layout(card_state, owner);
    return obj;
}
