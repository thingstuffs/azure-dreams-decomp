#include "shared/pad_state.h"
#include "common.h"
#include "frontend/card/message.h"
#include "main/data.h"

typedef struct S_804027F8_0 {
    s32 unk_00;
    u8 pad_04[0x4];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
    u8 pad_14[0xC];
    s32 * unk_20;
} S_804027F8_0;   /* arg0 in card_boot_handle_menu_actions_and_repeat */

extern s32 func_80056450(s32 selection, s32 step, u8 table_value);
extern void func_80063FF8(s32 code);
extern void resolve_apply(void *menu);
extern s32 process_global(s32 value);

/* Handles menu actions and directional selection with key repeat. */
void card_boot_handle_menu_actions_and_repeat(void *menu_arg)
{
    S_804027F8_0 *menu = menu_arg;
    s32 held_buttons;
    s32 pressed_buttons;
    s32 step;
    s32 repeat_ticks;

    held_buttons = boot_pad_state.held;
    step = 0;
    if (held_buttons != 0) {
        pressed_buttons = boot_pad_state.pressed;
        if (!(pressed_buttons & 0x40)) {
            if (pressed_buttons & 0x20) {
                s32 action_result;
                s32 *result_out;

                func_80063FF8(0x514);
                if (menu->unk_20 != 0) {
                    action_result = process_global(1);
                    result_out = menu->unk_20;
                    *result_out = action_result;
                } else {
                    process_global(1);
                }
            } else if (held_buttons & 0xA000) {
                if (pressed_buttons & 0xA000) {
                    menu->unk_10 = 0;
                    pressed_buttons = boot_pad_state.pressed;
                    if (pressed_buttons & 0x8000) {
                        step = -1;
                    } else if (pressed_buttons & 0x2000) {
                        step = 1;
                    }
                } else {
                    repeat_ticks = menu->unk_10;
                    if (repeat_ticks >= 3) {
                        if (held_buttons & 0x8000) {
                            step = -1;
                        } else if (held_buttons & 0x2000) {
                            step = 1;
                        }
                    } else {
                        menu->unk_10 = repeat_ticks + 1;
                    }
                }
            }
        }

        if (step != 0) {
            s32 selection;
            s32 menu_type;

            func_80063FF8(0x502);
            menu_type = menu->unk_08;
            selection = func_80056450(
                menu->unk_00, step, D_80408ADE[menu_type * 4]);
            menu->unk_00 = selection;
            resolve_apply(menu);
        }
    }
}
