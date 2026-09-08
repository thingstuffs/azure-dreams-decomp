#include "common.h"

typedef struct S_804027F8_0 {
    s32 unk_00;
    u8 pad_04[0x4];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
    u8 pad_14[0xC];
    s32 * unk_20;
} S_804027F8_0;   /* arg0 in func_804027F8 */



extern s32 D_801379A8;
extern s32 D_801379B0;
extern u8 D_80408ADE[];

extern s32 func_80056450(s32 arg0, s32 arg1, u8 arg2);
extern void func_80063FF8(s32 arg0);
extern void func_8040274C(void *arg0);
extern s32 func_8040343C(s32 arg0);

/* Handles menu actions and directional selection with key repeat. */
void func_804027F8(void *menu)
{
    s32 held_buttons;
    s32 pressed_buttons;
    s32 step;
    s32 repeat_ticks;

    held_buttons = D_801379A8;
    step = 0;
    if (held_buttons != 0) {
        menu = (u8 *)menu + 1;
        menu = (u8 *)menu - 1;
        pressed_buttons = D_801379B0;
        if (!(pressed_buttons & 0x40)) {
            if (pressed_buttons & 0x20) {
                s32 action_result;
                s32 *result_out;

                func_80063FF8(0x514);
                if (((S_804027F8_0 *)menu)->unk_20 != 0) {
                    action_result = func_8040343C(1);
                    result_out = ((S_804027F8_0 *)menu)->unk_20;
                    *result_out = action_result;
                } else {
                    func_8040343C(1);
                }
            } else if (held_buttons & 0xA000) {
                if (pressed_buttons & 0xA000) {
                    (*(s32 *)((u8 *)menu + 0x10)) = 0;
                    pressed_buttons = D_801379B0;
                    if (pressed_buttons & 0x8000) {
                        step = -1;
                    } else if (pressed_buttons & 0x2000) {
                        step = 1;
                    }
                } else {
                    repeat_ticks = ((S_804027F8_0 *)menu)->unk_10;
                    if (repeat_ticks >= 3) {
                        if (held_buttons & 0x8000) {
                            step = -1;
                        } else if (held_buttons & 0x2000) {
                            step = 1;
                        }
                    } else {
                        ((S_804027F8_0 *)menu)->unk_10 = repeat_ticks + 1;
                    }
                }
            }
        }

        if (step != 0) {
            s32 selection;
            s32 menu_type;

            func_80063FF8(0x502);
            menu_type = ((S_804027F8_0 *)menu)->unk_08;
            selection = func_80056450(
                ((S_804027F8_0 *)menu)->unk_00, step, D_80408ADE[menu_type * 4]);
            ((S_804027F8_0 *)menu)->unk_00 = selection;
            func_8040274C(menu);
        }
    }
}
