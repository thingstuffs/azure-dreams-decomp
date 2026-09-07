#include "common.h"

typedef struct S_800265B8_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    s32 unk_24;
    u8 pad_28[0x4];
    s32 unk_2C;
    s32 unk_30;
} S_800265B8_0;   /* arg0 in func_800265B8 */



extern s32 D_80083160[];

extern s32 func_8002168C(void);
extern void func_80021904(void);
extern void func_80025DC8(void *arg0);
extern void func_8002651C(void *arg0);
extern void func_80026920(void *arg0);
extern void func_80027AFC(s32 arg0, s32 arg1);
extern s32 func_80049DE8(s32 arg0, s32 arg1, s32 arg2);
extern void func_80053DA8(s32 arg0);

/* Handles menu navigation with button repeat and dispatches the selected action. */
void func_800265B8(u8 *menu)
{
    s32 held_buttons;
    s32 pressed_buttons;
    s32 repeat_buttons;
    s32 status;
    s32 repeat_ticks;
    s32 *controller;

    held_buttons = D_80083160[2];
    controller = D_80083160;
    status = 0;
    if (held_buttons != 0) {
        pressed_buttons = controller[4];
        if (pressed_buttons & 0x20) {
            func_80053DA8(0x515);
            goto perform_action;
        }
        if (pressed_buttons & 0x40) {
            func_80053DA8(0x503);
            func_8002651C(menu);
            goto finish_input;
        }
        if (held_buttons & 0x5000) {
            if (pressed_buttons & 0x5000) {
                ((S_800265B8_0 *)menu)->unk_30 = 0;
                pressed_buttons = controller[4];
                if (pressed_buttons & 0x1000) {
                    status = -1;
                } else if (pressed_buttons & 0x4000) {
                    status = 1;
                }
            } else {
                repeat_ticks = ((S_800265B8_0 *)menu)->unk_30;
                if (repeat_ticks >= 13) {
                    ((S_800265B8_0 *)menu)->unk_30 = repeat_ticks - 4;
                    repeat_buttons = controller[2];
                    if (repeat_buttons & 0x1000) {
                        status = -1;
                    } else if (repeat_buttons & 0x4000) {
                        status = 1;
                    }
                } else {
                    ((S_800265B8_0 *)menu)->unk_30 = repeat_ticks + 1;
                }
            }
        }

finish_input:
        if (status != 0) {
            func_80053DA8(0x502);
            ((S_800265B8_0 *)menu)->unk_2C =
                func_80049DE8(((S_800265B8_0 *)menu)->unk_2C, status, 5);
            func_80025DC8(menu);
        }
    }

    status = func_8002168C();
    func_80021904();
    if (status == 0) {
        return;
    }
    if (status == 1) {
        return;
    }

perform_action:
    func_80026920(menu - 0x20);
    func_80027AFC(((S_800265B8_0 *)menu)->unk_20, ((S_800265B8_0 *)menu)->unk_24);
}
