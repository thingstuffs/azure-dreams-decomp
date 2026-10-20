#include "common.h"


extern s32 D_801379A8;
extern s32 D_801379B0;

extern s32 func_80058FF0(s32 value, s32 direction, s32 amount);
extern void func_80063FF8(s32 sound);
extern s32 card_devkit_poll_stable_slot_state(void);
extern void submit_stored_and_queried_boot_values(void);
extern void card_devkit_highlight_selected_load_slot(void *object);
extern void reset_menu_object_state(void *object);
extern void func_804070C4(void *object);
extern void allocate_or_reuse_effect_and_install_callback(s32 field20, s32 field24);


typedef struct S_80406DA0_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    s32 unk_24;
    u8 pad_28[0x4];
    s32 unk_2C;
    s32 unk_30;
} S_80406DA0_0;   /* object in handle_menu_selection_input */

/* Handles menu selection, held-button repeats, and menu exit. */
void handle_menu_selection_input(void *object)
{
    s32 held_buttons;
    s32 pressed_buttons;
    s32 direction;
    s32 repeat_ticks;
    s32 repeat_buttons;
    s32 *buttons;

    buttons = &D_801379A8;
        held_buttons = buttons[0];
    direction = 0;
    if (held_buttons != 0) {
        buttons = &D_801379B0;
        pressed_buttons = buttons[0];
        if (pressed_buttons & 0x40) {
            func_80063FF8(0x515);
            func_804070C4((u8 *)object - 0x20);
            allocate_or_reuse_effect_and_install_callback(((S_80406DA0_0 *)object)->unk_20, ((S_80406DA0_0 *)object)->unk_24);
            return;
        }
        if (pressed_buttons & 0x20) {
            func_80063FF8(0x514);
            reset_menu_object_state(object);
        } else if (held_buttons & 0x5000) {
            if (pressed_buttons & 0x5000) {
                buttons = (s32 *)((u8 *)object + 0x30);
                *buttons = 0;
                buttons = &D_801379B0;
        pressed_buttons = buttons[0];
                if (pressed_buttons & 0x1000) {
                    direction = -1;
                } else if (pressed_buttons & 0x4000) {
                    direction = 1;
                }
            } else {
                repeat_ticks = ((S_80406DA0_0 *)object)->unk_30;
                if (repeat_ticks >= 13) {
                    (*(s32 *)((u8 *)object + (0x30))) = repeat_ticks - 4;
                    buttons = &D_801379A8;
        repeat_buttons = buttons[0];
                    if (repeat_buttons & 0x1000) {
                        direction = -1;
                    } else if (repeat_buttons & 0x4000) {
                        direction = 1;
                    }
                } else {
                    ((S_80406DA0_0 *)object)->unk_30 = repeat_ticks + 1;
                }
            }
        }
        if (direction != 0) {
            func_80063FF8(0x502);
            ((S_80406DA0_0 *)object)->unk_2C =
                func_80058FF0(((S_80406DA0_0 *)object)->unk_2C, direction, 5);
            card_devkit_highlight_selected_load_slot(object);
        }
    }

    direction = card_devkit_poll_stable_slot_state();
    submit_stored_and_queried_boot_values();
    if (direction == 0) {
        return;
    }
    if (direction == 1) {
        return;
    }
    func_804070C4((u8 *)object - 0x20);
    allocate_or_reuse_effect_and_install_callback(((S_80406DA0_0 *)object)->unk_20, ((S_80406DA0_0 *)object)->unk_24);
}
