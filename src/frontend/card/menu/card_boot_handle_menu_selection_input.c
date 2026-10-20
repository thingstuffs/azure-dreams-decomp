#include "shared/pad_state.h"
#include "common.h"


typedef struct StatePair {
    s32 first;
    s32 second;
} StatePair;

extern s8 D_8008CA34;
extern s32 D_804090F8[];
extern s32 D_80400854;
extern s32 D_80400860;

extern void func_8003FA78(void *display_object, s32 state_entry);
extern void func_8003FD58(s32 value0, s32 value1, s32 value2, s32 value3);
extern void func_80063FF8(s32 sound_code);
extern void func_804008A0(s32 slot_index);
extern void func_80400EF8(void);
extern StatePair *card_devkit_debounce_channel_status(void);
extern void submit_stored_and_queried_boot_values(void);
extern void assert_slot_store_value_and_process_state(s32 slot_addr, s32 slot_value);
extern void update_embedded_selected_slot_outputs(s32 slot_addr, StatePair *display_state, s32 *state_changed);
extern void card_boot_update_object_state_and_callback(void);
extern void memory_process_handles_and_mark_object(void *object);


typedef struct S_804081AC_0 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_804081AC_0;   /* object in card_boot_handle_menu_selection_input */

/* Handles menu selection input and refreshes the displayed state pair. */
void card_boot_handle_menu_selection_input(void *menu)
{
    s32 state_changed[2];
    StatePair *state;
    StatePair *display_state;
    s32 buttons;
    s32 button_flags;
    s32 selection_changed;
    s32 old_selection;

    buttons = D_801379A8.held;
    selection_changed = 0;
    if (buttons != 0) {
        button_flags = D_801379A8.pressed;
        if (button_flags & 0x40) {
            s32 *linked_object;

            func_80063FF8(0x515);
            memory_process_handles_and_mark_object((u8 *)menu - 0x20);
            D_8008CA34 = 2;
            func_80400EF8();
            func_8003FD58(0, 0xF, 0, 0);
            linked_object = (*(s32 * *)((u8 *)menu + 0x14));
            ((S_804081AC_0 *)linked_object)->unk_1E |= 0x2000;
        } else if (button_flags & 0x20) {
            func_80063FF8(0x514);
            func_804008A0((*(s32 *)((u8 *)menu + 0xC)));
            (*(s32 *)((u8 *)menu + 0x34)) = 0;
            (*(void * *)((u8 *)menu + -0x10)) = card_boot_update_object_state_and_callback;
            return;
        } else if (buttons & 0xA000) {
            if (buttons & 0x8000) {
                old_selection = (*(s32 *)((u8 *)menu + 0xC));
                (*(s32 *)((u8 *)menu + 0xC)) = 0;
                if (old_selection != 0) {
                    selection_changed = 1;
                }
            } else {
                old_selection = (*(s32 *)((u8 *)menu + 0xC));
                if (old_selection == 0) {
                    selection_changed = 1;
                }
                (*(s32 *)((u8 *)menu + 0xC)) = 1;
            }
        }

        if (selection_changed != 0) {
            func_80063FF8(0x502);
            assert_slot_store_value_and_process_state((*(s32 *)((u8 *)menu + 0x24)), (*(s32 *)((u8 *)menu + 0xC)));
        }
    }

    state = card_devkit_debounce_channel_status();
    state_changed[0] = state->first != (*(s32 *)((u8 *)menu + 0x18));
    state_changed[1] = state->second != (*(s32 *)((u8 *)menu + 0x1C));
    display_state = state;
    (*(StatePair *)((u8 *)menu + 0x18)) = *state;
    update_embedded_selected_slot_outputs((*(s32 *)((u8 *)menu + 0x24)), display_state, state_changed);
    func_8003FA78(&D_80400854, D_804090F8[state->first]);
    func_8003FA78(&D_80400860, D_804090F8[state->second]);
    submit_stored_and_queried_boot_values();

    return;
}
