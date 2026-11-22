#include "common.h"
#include "frontend/card.h"
#include "frontend/card/save.h"
#include "frontend/card/save_operation.h"
#include "frontend/card/service.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"
#include "shared/object_node.h"
#include "frontend/card/server_aliases.h"

extern volatile s32 boot_pad_state;
extern volatile s32 boot_pressed_buttons;

/* Per-frame menu step: handle the pad's edge/repeat flags, move the cursor and run the post-step hooks. */
void card_dev_update_menu_input(CardSaveOperationBody *root)
{
    s32 action = 0;
    s32 *repeat_ticks = &root->repeat_ticks;
    s32 entry_flags;
    s32 flags8;
    s32 flags10;
    s32 value;
    s32 side;
    s32 result;

    entry_flags = boot_pad_state;
    if (entry_flags != 0) {
        s32 flags20;
        s32 flags5000;

        flags20 = boot_pressed_buttons;
        if (flags20 & 0x40) {
            SD_Call_80063FF8(0x515);
            NODE_HEADER(root)->update_callback = refresh_save_slot_selection_and_resume_menu_input;
        }
        flags10 = boot_pressed_buttons;
        if (flags10 & 0x20) {
            SD_Call_80063FF8(0x514);
            select_save_slot_callback(root);
        } else {
            flags5000 = boot_pad_state;
            if (flags5000 & 0x5000) {
                side = flags10 & 0x5000;
                if (side != 0) {
                    *repeat_ticks = 0;
                    flags10 = boot_pressed_buttons;
                    if (flags10 & 0x1000) {
                        action = -1;
                    } else if (flags10 & 0x4000) {
                        action = 1;
                    }
                } else {
                    value = *repeat_ticks;
                    if (value >= 13) {
                        side = value - 2;
                        *repeat_ticks = side;
                        flags8 = boot_pad_state;
                        if (flags8 & 0x1000) {
                            action = -1;
                        } else if (flags8 & 0x4000) {
                            action = 1;
                        }
                    } else {
                        side = value + 1;
                        *repeat_ticks = side;
                    }
                }
            }
        }

        if (action != 0) {
            SD_Call_80063FF8(0x502);
            value = advance_card_menu_index_80058FF0(root->entry_index, action, 5);
            root->entry_index = value;
            card_devkit_refresh_save_slot_pair_highlights(root);
        }
    }

    result = card_devkit_poll_stable_slot_state();
    card_dev_print_status();
    if (result == 0) {
        return;
    }
    if (result == 1) {
        return;
    }
    release_card_screen_parts(NODE_HEADER(root));
    create_card_dev_slot_screen_effect(root->request, 0);

    return;
}
