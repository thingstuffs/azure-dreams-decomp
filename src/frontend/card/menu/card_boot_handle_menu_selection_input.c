#include "shared/pad_state.h"
#include "common.h"
#include "shared/object_node.h"
#include "frontend/libcard/card_chooser.h"
#include "frontend/card/service.h"
#include "main/data.h"
#include "frontend/card/menu.h"
#include "frontend/card/server_imports.h"
#include "frontend/card.h"
#include "frontend/card/server_aliases.h"








/* Handles menu selection input and refreshes the displayed state pair. */
void card_boot_handle_menu_selection_input(CardChooserBody *menu)
{
    s32 state_changed[2];
    s32 *state;
    s32 *display_state;
    s32 buttons;
    s32 button_flags;
    s32 selection_changed;
    s32 old_selection;

    buttons = boot_pad_state.held;
    selection_changed = 0;
    if (buttons != 0) {
        button_flags = boot_pad_state.pressed;
        if (button_flags & 0x40) {
            ObjectNodeHeader *linked_object;

            SD_Call_80063FF8(0x515);
            release_devkit_node_handles(NODE_HEADER(menu));
            card_dev_effect_mode = 2;
            card_dev_close_events();
            begin_card_chooser_exit_transition_8003FD58(0, 0xF, 0, 0);
            linked_object = menu->request;
            linked_object->flags |= 0x2000;
        } else if (button_flags & 0x20) {
            SD_Call_80063FF8(0x514);
            set_card_selection_state(menu->selected_channel);
            menu->unk_34 = 0;
            NODE_HEADER(menu)->update_callback = card_boot_update_object_state_and_callback;
            return;
        } else if (buttons & 0xA000) {
            if (buttons & 0x8000) {
                old_selection = menu->selected_channel;
                menu->selected_channel = 0;
                if (old_selection != 0) {
                    selection_changed = 1;
                }
            } else {
                old_selection = menu->selected_channel;
                if (old_selection == 0) {
                    selection_changed = 1;
                }
                menu->selected_channel = 1;
            }
        }

        if (selection_changed != 0) {
            SD_Call_80063FF8(0x502);
            assert_slot_store_value_and_process_state(menu->choices, menu->selected_channel);
        }
    }

    state = card_devkit_debounce_channel_status();
    state_changed[0] = state[0] != menu->card_presence.first;
    state_changed[1] = state[1] != menu->card_presence.second;
    display_state = state;
    __builtin_memcpy(&menu->card_presence, state, sizeof(menu->card_presence));
    update_embedded_selected_slot_outputs(menu->choices, display_state, state_changed);
    card_diagnostic_printf_8003FA78(dev_card_first_status_format, dev_card_channel_status_names[state[0]]);
    card_diagnostic_printf_8003FA78(dev_card_second_status_format, dev_card_channel_status_names[state[1]]);
    card_dev_print_status();

    return;
}
