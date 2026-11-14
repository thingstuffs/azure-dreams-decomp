#include "shared/pad_state.h"
#include "common.h"
#include "shared/object_node.h"
#include "frontend/libcard/card_chooser.h"
#include "frontend/card/service.h"
#include "main/data.h"
#include "frontend/card/menu.h"
#include "frontend/card/server_imports.h"
#include "frontend/card.h"




#include "frontend/card/effect_mode_data.h"

extern void func_804008A0(s32 slot_index);
extern void submit_stored_and_queried_boot_values(void);
extern void assert_slot_store_value_and_process_state(s32 slot_addr, s32 slot_value);
extern void update_embedded_selected_slot_outputs(s32 slot_addr, CardChooserPresence *display_state, s32 *state_changed);
extern void release_devkit_node_handles(void *object);



/* Handles menu selection input and refreshes the displayed state pair. */
void card_boot_handle_menu_selection_input(CardChooserBody *menu)
{
    s32 state_changed[2];
    CardChooserPresence *state;
    CardChooserPresence *display_state;
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

            func_80063FF8(0x515);
            release_devkit_node_handles((u8 *)menu - 0x20);
            card_dev_effect_mode = 2;
            card_dev_close_events();
            func_8003FD58(0, 0xF, 0, 0);
            linked_object = menu->request;
            linked_object->flags |= 0x2000;
        } else if (button_flags & 0x20) {
            func_80063FF8(0x514);
            func_804008A0(menu->selected_channel);
            menu->unk_34 = 0;
            ((ObjectNodeHeader *)menu - 1)->update_callback = card_boot_update_object_state_and_callback;
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
            func_80063FF8(0x502);
            assert_slot_store_value_and_process_state((*(s32 *)((u8 *)menu + 0x24)), menu->selected_channel);
        }
    }

    state = card_devkit_debounce_channel_status();
    state_changed[0] = state->first != menu->card_presence.first;
    state_changed[1] = state->second != menu->card_presence.second;
    display_state = state;
    menu->card_presence = *state;
    update_embedded_selected_slot_outputs((*(s32 *)((u8 *)menu + 0x24)), display_state, state_changed);
    func_8003FA78(&D_80400854, D_804090F8[state->first]);
    func_8003FA78(&D_80400860, D_804090F8[state->second]);
    submit_stored_and_queried_boot_values();

    return;
}
