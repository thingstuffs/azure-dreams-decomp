#include "shared/audio_commands.h"
#include "common.h"
#include "shared/object_node.h"
#include "frontend/libcard/card_chooser.h"
#include "shared/game_work.h"
#include "frontend/libcard/state.h"




extern u8 scene_mode_code;

extern void card_boot_select_channel_mode(s32 mode_enabled); /* Unprototyped: retail call passes a different argument count */
extern s32 *card_boot_debounce_card_presence(void);
#include "modules/main_server_ship_interfaces.h"
#include "frontend/libcard/interfaces.h"
#include "engine/resource.h"
#include "engine/scene.h"
#include "frontend/card.h"
#include "frontend/libcard.h"
#include "slus.h"
extern void restore_entity_flag_ten(void);



/* Handles menu input and refreshes the displayed state. */
void card_boot_update_card_chooser_input(CardChooserBody *body)
{
    Object_800128C8 *menu = (Object_800128C8 *)body;
    s32 state_changed[2];
    CardChooserPresence *state;
    CardChooserPresence *display_state;
    s32 buttons;
    s32 button_flags;
    s32 selection_changed;
    s32 selection;

    buttons = g_game_work.buttons;
    selection_changed = 0;
    if (buttons != 0) {
        button_flags = (g_game_work.pressed_buttons);
        if (button_flags & 0x20) {
            ObjectNodeHeader *object;

            SD_Call(AUDIO_CANCEL);
            card_boot_destroy_card_chooser(((void *)menu) - 0x20);
            card_boot_close_events_and_resume_timer();
            if (scene_mode_code == 3) {
                request_scene_dispatch_state(3);
            } else {
                create_deferred_resource_transition_task(0, 0, 0, 0);
                object = ((CardChooserBody *)menu)->request;
                object->flags |= 0x2000;
                if (((CardChooserBody *)menu)->mode == 2) {
                    restore_entity_flag_ten();
                }
            }
        } else if (button_flags & 0x40) {
            SD_Call(AUDIO_MENU_CONFIRM);
            card_boot_select_channel_mode(((CardChooserBody *)menu)->selected_channel);
            menu->unk_34 = 0;
            ((ObjectNodeHeader *)menu - 1)->update_callback = card_boot_poll_card_chooser_status;
            return;
        } else if (buttons & 0xA000) {
            if (buttons & 0x8000) {
                selection = ((CardChooserBody *)menu)->selected_channel;
                if (selection != 0) {
                    selection_changed = 1;
                }
                ((CardChooserBody *)menu)->selected_channel = 0;
            } else {
                selection = ((CardChooserBody *)menu)->selected_channel;
                if (selection == 0) {
                    selection_changed = 1;
                }
                ((CardChooserBody *)menu)->selected_channel = 1;
            }
        }

        if (selection_changed != 0) {
            SD_Call(AUDIO_CURSOR_MOVE);
            card_boot_set_paired_choice_selection(menu->unk_24, ((CardChooserBody *)menu)->selected_channel);
        }
    }

    state = card_boot_debounce_card_presence();
    state_changed[0] = state->first != ((CardChooserBody *)menu)->card_presence.first;
    state_changed[1] = state->second != ((CardChooserBody *)menu)->card_presence.second;
    display_state = state;
    ((CardChooserBody *)menu)->card_presence = *state;
    card_boot_update_paired_choice_animations((*(ObjectNodeHeader **)((u8 *)menu + 0x24)), display_state, state_changed);
    no_op_card_stub();

    return;
}
