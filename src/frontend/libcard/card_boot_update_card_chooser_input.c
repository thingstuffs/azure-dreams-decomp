#include "common.h"
#include "shared/game_work.h"


typedef struct StatePair {
    s32 first;
    s32 second;
} StatePair;

extern u8 D_80082E6B;

extern void card_boot_select_channel_mode(s32 mode_enabled);
extern StatePair *card_boot_debounce_card_presence(void);
#include "modules/main_server_ship_interfaces.h"
extern void card_boot_set_paired_choice_selection(s32 object_addr, s32 value);
extern void card_boot_update_paired_choice_animations(s32 base_addr, StatePair *display_state, s32 *changed_flags);
#include "frontend/libcard/interfaces.h"
extern void card_boot_destroy_card_chooser(void *entry);
extern void func_80040AA0(s32 requested_state);
extern void create_deferred_resource_transition_task(s32 mode, s32 lookup_id, s32 payload_word_0, s32 payload_word_4);
extern void SD_Call(s32 flags);
extern void restore_entity_flag_ten(void);
extern void card_boot_poll_card_chooser_status(void);


typedef struct S_8002789C_0 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_8002789C_0;   /* object in card_boot_update_card_chooser_input */

/* Handles menu input and refreshes the displayed state. */
void card_boot_update_card_chooser_input(void *menu)
{
    s32 state_changed[2];
    StatePair *state;
    StatePair *display_state;
    s32 buttons;
    s32 button_flags;
    s32 selection_changed;
    s32 selection;

    buttons = g_game_work.buttons;
    selection_changed = 0;
    if (buttons != 0) {
        button_flags = ((s32)g_game_work.pressed_buttons);
        if (button_flags & 0x20) {
            s32 *object;

            SD_Call(0x515);
            card_boot_destroy_card_chooser((u8 *)menu - 0x20);
            card_boot_close_events_and_resume_timer();
            if (D_80082E6B == 3) {
                func_80040AA0(3);
            } else {
                create_deferred_resource_transition_task(0, 0, 0, 0);
                object = (*(s32 * *)((u8 *)menu + 0x14));
                ((S_8002789C_0 *)object)->unk_1E |= 0x2000;
                if ((*(s32 *)((u8 *)menu + 0)) == 2) {
                    restore_entity_flag_ten();
                }
            }
        } else if (button_flags & 0x40) {
            SD_Call(0x503);
            card_boot_select_channel_mode((*(s32 *)((u8 *)menu + 0xC)));
            (*(s32 *)((u8 *)menu + 0x34)) = 0;
            (*(void * *)((u8 *)menu + -0x10)) = card_boot_poll_card_chooser_status;
            return;
        } else if (buttons & 0xA000) {
            if (buttons & 0x8000) {
                selection = (*(s32 *)((u8 *)menu + 0xC));
                if (selection != 0) {
                    selection_changed = 1;
                }
                (*(s32 *)((u8 *)menu + 0xC)) = 0;
            } else {
                selection = (*(s32 *)((u8 *)menu + 0xC));
                if (selection == 0) {
                    selection_changed = 1;
                }
                (*(s32 *)((u8 *)menu + 0xC)) = 1;
            }
        }

        if (selection_changed != 0) {
            SD_Call(0x502);
            card_boot_set_paired_choice_selection((*(s32 *)((u8 *)menu + 0x24)), (*(s32 *)((u8 *)menu + 0xC)));
        }
    }

    state = card_boot_debounce_card_presence();
    state_changed[0] = state->first != (*(s32 *)((u8 *)menu + 0x18));
    state_changed[1] = state->second != (*(s32 *)((u8 *)menu + 0x1C));
    display_state = state;
    (*(StatePair *)((u8 *)menu + 0x18)) = *state;
    card_boot_update_paired_choice_animations((*(s32 *)((u8 *)menu + 0x24)), display_state, state_changed);
    no_op_card_stub();

    return;
}
