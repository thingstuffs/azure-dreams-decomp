#include "common.h"

typedef struct S_80406368_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x4];
    s32 unk_28;
    u8 pad_2C[0x4];
    s32 unk_30;
    u8 pad_34[0x10];
    s32 unk_44;
    s32 unk_48;
} S_80406368_0;   /* menu in handle_object_menu_input */


extern s32 D_801379A8;
extern s32 D_801379B0;

extern void func_80063FF8(s32 sound_code);
extern s32  func_80058FF0(s32 selection_index, s32 direction, s32 selection_count);
extern s32  card_devkit_poll_stable_slot_state(void);
extern void submit_stored_and_queried_boot_values(void);
extern void card_devkit_refresh_save_slot_selection(void *menu);
extern void invoke_indexed_object_callback(void *menu);
extern void func_80406358(void *menu);
extern void propagate_object_high_bit_flags(void *object);
extern void allocate_or_reuse_effect_and_install_callback(s32 value0, s32 value1);

/* Handles menu navigation, button actions, and display refreshes. */
void handle_object_menu_input(void *menu)
{
    s32 held_buttons;
    s32 pressed_buttons;
    s32 nav_result;
    s32 needs_refresh;
    s32 repeat_ticks;
    s32 *held_p = &D_801379A8;
    s32 *press_p = &D_801379B0;

    held_buttons = D_801379A8;
    nav_result = 0;
    needs_refresh = 0;
    if (held_buttons != 0) {
        pressed_buttons = D_801379B0;
        if (pressed_buttons & 0x40) {
            func_80063FF8(0x515);
            propagate_object_high_bit_flags((u8 *) menu - 0x20);
            allocate_or_reuse_effect_and_install_callback(((S_80406368_0 *)menu)->unk_20, 0);
            return;
        } else if (pressed_buttons & 0x20) {
            func_80063FF8(0x514);
            if (((S_80406368_0 *)menu)->unk_48 == 0) {
                func_80406358(menu);
                needs_refresh = 1;
            } else {
                invoke_indexed_object_callback(menu);
            }
        } else if (held_buttons & 0x5000) {
            if (pressed_buttons & 0x5000) {
                (*(s32 *)((u8 *)menu + 0x30)) = 0;
                if (*press_p & 0x1000) {
                    nav_result = -1;
                } else if (*press_p & 0x4000) {
                    nav_result = 1;
                }
            } else {
                repeat_ticks = ((S_80406368_0 *)menu)->unk_30;
                if (repeat_ticks >= 13) {
                    (*(s32 *)((u8 *)menu + 0x30)) = repeat_ticks - 4;
                    if (*held_p & 0x1000) {
                        nav_result = -1;
                    } else if (*held_p & 0x4000) {
                        nav_result = 1;
                    }
                } else {
                    ((S_80406368_0 *)menu)->unk_30 = repeat_ticks + 1;
                }
            }
        } else if (held_buttons & 0xA000) {
            if (held_buttons & 0x2000) {
                ((S_80406368_0 *)menu)->unk_48 = 1;
            } else {
                ((S_80406368_0 *)menu)->unk_48 = 0;
            }
            needs_refresh = 1;
        }

        if (nav_result != 0) {
            func_80063FF8(0x502);
            if (((S_80406368_0 *)menu)->unk_48 == 1) {
                ((S_80406368_0 *)menu)->unk_28 = func_80058FF0(((S_80406368_0 *)menu)->unk_28, nav_result, 5);
            } else {
                ((S_80406368_0 *)menu)->unk_44 = func_80058FF0(((S_80406368_0 *)menu)->unk_44, nav_result, 4);
            }
            card_devkit_refresh_save_slot_selection(menu);
        }
    }

    nav_result = card_devkit_poll_stable_slot_state();
    submit_stored_and_queried_boot_values();
    if (nav_result != 0) {
        if (nav_result != 1) {
            propagate_object_high_bit_flags((u8 *) menu - 0x20);
            allocate_or_reuse_effect_and_install_callback(((S_80406368_0 *)menu)->unk_20, 0);
        }
    }
    if (needs_refresh != 0) {
        card_devkit_refresh_save_slot_selection(menu);
    }
}
